const commentRouter = require('express').Router()
const Comment = require('../models/comment')

commentRouter.get('/', async (request, response) => {
  const comments =  await Comment.find({})
  response.status(200).json(comments)
})

module.exports = commentRouter