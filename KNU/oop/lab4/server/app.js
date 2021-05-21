const config = require('./utils/config')
const express = require('express')
require('express-async-errors')
const blogsRouter = require ('./controllers/blogs')
const usersRouter = require ('./controllers/users')
const loginRouter = require ('./controllers/login')
const commentRouter = require ('./controllers/comments')
const app = express()
const mongoose = require('mongoose')
const cors = require('cors')
const logger = require('./utils/logger')
const middleware = require('./utils/middleware')


app.use(cors())
app.use(express.json())
app.use(middleware.requestLogger)
app.use(middleware.tokenExtractor)


app.use('/api/blogs', blogsRouter)
app.use('/api/users', usersRouter)
app.use('/api/login', loginRouter)
app.use('/api/comments', commentRouter)
if (process.env.NODE_ENV === 'test' || process.env.NODE_ENV === 'test_console') {
  const testingRouter = require('./controllers/testing')
  app.use('/api/testing', testingRouter)
}

app.use(middleware.unknownEndpoint)
app.use(middleware.errorHandler)


mongoose.connect(config.MONGODB_URI, { useNewUrlParser: true, useUnifiedTopology: true })
  .then( () => {logger.info ('connected to MongoDB')})
  .catch( error => {logger.error('error while connecting to Mongo:', error.message)})

module.exports = app
