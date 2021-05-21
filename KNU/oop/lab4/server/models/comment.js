const mongoose = require('mongoose')
mongoose.set('useFindAndModify', false)
const commentSchema = new mongoose.Schema({
  content: {
    type: String,
    required: true
  },
  blog: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Blog'
  }
})


commentSchema.set ('toJSON', {
  transform: (document, returnedObject) => {
    returnedObject.id = returnedObject._id.toString()
    delete returnedObject.__v
    delete returnedObject._id
  }
})

const Comment = mongoose.model('Comment', commentSchema)

module.exports = Comment