const Blog = require ('../models/blog')
const User = require ('../models/user')
const bcrypt = require ('bcrypt')
const initialBlogs = [
  {
    title: '10 reasons why you should get a job',
    author: 'Your conscience',
    url: 'yourbrain.com',
    likes: 1
  },
  {
    title: 'Problems are opportunities',
    author: 'Tina Silig',
    url: 'yourpurpose.com',
    likes: 2

  },
  {
    title: 'The solution to your problems are where you haven\'t looked yet',
    author: 'Jordan Peterson',
    url: 'lifeadvice.com',
    likes: 2
  }
]

const initialUserPassword = 'secret'
const passwordHash = () => {return bcrypt.hashSync (initialUserPassword, 10)}
const initialUser = {
  username: 'root',
  password: passwordHash(),
  name: 'test'
}


const nonexistingId = () => {
  const blog = new Blog ({
    title: 'toremove',
    author: 'JEST',
    url: 'testingsucks.com',
    likes: 100
  })
  return blog._id.toString()
}

const blogsInDB = async () => {
  const blogs = await Blog.find({})
  return blogs.map (blog => blog.toJSON())
}

const usersInDB = async () => {
  const users = await User.find({})
  return users.map (user => user.toJSON())
}


module.exports = {
  initialBlogs,
  initialUser,
  initialUserPassword,
  nonexistingId,
  blogsInDB,
  usersInDB
}