const jwt = require('jsonwebtoken')
const blogsRouter = require('express').Router()
const Blog = require ('../models/blog')
const User = require ('../models/user')
const Comment = require('../models/comment')

// implement multiple populates
blogsRouter.get('/', async (request, response) => {
  const allBlogs = await Blog.find({})
    .populate('user', { blogs: 0 })
    .populate('comments', { blog: 0 })
  response.status(200).json(allBlogs)
})


blogsRouter.post('/', async (request, response) => {
  if (typeof request.body.likes === 'undefined')
  {
    request.body.likes = 0
  }

  const body = request.body

  const user = jwt.verify (request.token, process.env.SECRET)

  if (!request.token || !user)
  {
    return response.status(401).json({ error: 'No JWT token/token is invalid' })
  }
  const author  = await User.findById(user.id)

  const newBlog = {
    ...body,
    user: author._id
  }

  const blog = new Blog(newBlog)

  author.blogs = author.blogs.concat(blog._id)
  await User.findByIdAndUpdate(author._id, author)

  const savedBlog = await blog.save()
  response.status(201).json(savedBlog)
})

blogsRouter.delete('/:id', async (request, response) => {
  const decodedToken = jwt.verify (request.token, process.env.SECRET)
  const user = await User.findOne({ username: decodedToken.username })

  const blogToDelete = user.blogs.filter( blog => {
    return (blog.toString() === request.params.id.toString())
  })

  // if there is no user, the token is invalid or the user didn't create this blog
  if (!user || !decodedToken || blogToDelete.length === 0)
  {
    return response.status(401).json({ error: 'invalid token / wrong user' })
  }

  const blogsForUpdatedUser = user.blogs.filter( blog => {
    return !(blog.toString() === request.params.id.toString())
  })


  const updatedUser = {
    ...user._doc,
    blogs: blogsForUpdatedUser
  }

  await User.findByIdAndUpdate(decodedToken.id, updatedUser)
  await Blog.findByIdAndRemove(request.params.id)
  response.status(204).end()
})

blogsRouter.put('/:id', async (request, response) => {
  const updatedBlog = request.body
  console.log('body:', updatedBlog)
  const updatedBlogWithID = await Blog
    .findByIdAndUpdate(request.params.id, updatedBlog, { new: true })
    .populate('user', { blogs: 0 })
    .populate('comments', { blog: 0 })

  console.log('updated blog:',updatedBlogWithID)
  if (updatedBlogWithID) {
    response.status(201).json(updatedBlogWithID)
  }
  else
  {
    response.status(404).end()
  }
})



blogsRouter.get('/comments', async (request, response) => {
  const comments =  await Comment.find({})
  response.status(200).json(comments)
})

blogsRouter.post ('/:id/comments', async (request, response) => {
  const body = request.body
  console.log(request.params.id)
  const blog = await Blog.findById(request.params.id)

  const comment = {
    content: body.comment,
    blog: blog._id
  }
  console.log('Comment', comment)
  const commentDocument = new Comment(comment)

  blog.comments = blog.comments.concat(commentDocument._id)

  console.log('Blog', blog)
  await Blog.findByIdAndUpdate(blog._id, blog)

  const savedComment = await commentDocument.save()

  response.status(201).json(savedComment)
})

module.exports = blogsRouter