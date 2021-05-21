const _ = require('lodash')

const dummy = (blogs) => {
  return 1
}

const totalLikes = (blogs) => {
  return blogs.map(blog => blog.likes)
    .reduce((sum, likesForBlog) => sum + likesForBlog, 0)
}

const favouriteBlog = (blogs) => {
  if (blogs.length === 0) return null
  const formattedBlogs = blogs.map (blog => {
    return {
      title: blog.title,
      author: blog.author,
      likes: blog.likes
    }
  })
  return formattedBlogs [
    formattedBlogs
      .map(blog => blog.likes)
      .reduce((iMax, curBlogLikes, i, likesArray) => {
        return (curBlogLikes > likesArray[iMax] ? i : iMax)
      }, 0)
  ]
}

// implement mostBlogs
// https://lodash.com/docs/4.17.15
const mostBlogs = (blogs) => {
  if (blogs.length === 0) return null
  const authorBlogMap = _.countBy(blogs, 'author')
  const authorOfMostBlogs =_.maxBy(Object.keys(authorBlogMap), (author) => {
    return authorBlogMap[author]
  })
  return (
    {
      author: authorOfMostBlogs,
      blogs: authorBlogMap[authorOfMostBlogs]
    }
  )
}

const mostLikes = (blogs) => {
  if (blogs.length === 0) return null
  const authorLikesMap = {}
  blogs.forEach(blog => authorLikesMap[blog.author] =
    (!isNaN(authorLikesMap[blog.author]))
      ? authorLikesMap[blog.author] + blog.likes
      : blog.likes
  )
  const authorWithMostLikes = _.maxBy(Object.keys(authorLikesMap), (author) => {
    return authorLikesMap[author]
  })
  return (
    {
      author: authorWithMostLikes,
      likes: authorLikesMap[authorWithMostLikes]
    }
  )
}

module.exports = {
  dummy,
  totalLikes,
  favouriteBlog,
  mostBlogs,
  mostLikes
}