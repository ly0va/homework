import React, {useState} from 'react'
import {useDispatch} from 'react-redux'
import { addComment } from '../reducers/BlogsReducer'
import {Button, TextField} from '@material-ui/core'
import flexInput from '../styles/flexInput'
const CommentForm = ({blog}) => {
  const dispatch = useDispatch()

  const [comment, setComment] = useState('')

  const handleSubmit = async (event) => {
    event.preventDefault()
    console.log(blog.id)
    await dispatch(addComment({comment}, blog.id))
    setComment('')
    console.log('submitted hehehehe')
  }

  const handleCommentChange = (event) => {
    setComment(event.target.value)
  }

  return (
    <div style = {{marginTop: 10}}>
      <form onSubmit = {handleSubmit} style = {flexInput}>
        <TextField
          value = {comment}
          onChange = {handleCommentChange}
          label = 'Your comment'
          variant="outlined"
        >
        </TextField>
        <Button variant="contained" type = 'submit' style = {{marginLeft: 5}}>
          add comment
        </Button>
      </form>
    </div>
  )
}

export default CommentForm