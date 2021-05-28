import React, {useState} from 'react'
import {useDispatch} from 'react-redux'
import {setNotification} from '../reducers/NotificationReducer'
import {Button, TextField} from '@material-ui/core'
import flexInput from '../styles/flexInput'
const NewBlogForm = ({ addBlog }) =>
{
  const dispatch = useDispatch()
  const emptyBlog = {
    author: '',
    title: '',
    likes: 0,
    url: ''
  }
  const [newBlog, setNewBlog] = useState(emptyBlog)

  const createBlog = async (event) =>
  {
    event.preventDefault()
    try
    {
      await addBlog(newBlog)
      setNewBlog(emptyBlog)
    }
    catch (exception)
    {
      dispatch(setNotification({
        content: exception,
        isGood: false
      }))
    }
  }


  return (
    <form onSubmit = {createBlog} className = 'newBlogForm'>
      <div style = {flexInput}>
        Title:
        <TextField
          id = 'title'
          type = 'text'
          value = {newBlog.title}
          onChange = {({ target }) => setNewBlog(
            {
              ...newBlog,
              title: target.value
            }
          )}
        >
        </TextField>
      </div>
      <div style = {flexInput}>
        Author:
        <TextField
          id = 'author'
          type = 'text'
          value = {newBlog.author}
          onChange = {({ target }) => setNewBlog(
            {
              ...newBlog,
              author: target.value
            }
          )}
        >
        </TextField>
      </div>
      <div style = {flexInput}>
        URL:
        <TextField
          id = 'url'
          type = 'text'
          value = {newBlog.url}
          onChange = {({ target }) => setNewBlog(
            {
              ...newBlog,
              url: target.value
            }
          )}
        >
        </TextField>
      </div>
      <Button variant="contained"
        id = 'createNewBlogButton'
        type = 'submit'
      >
         Create new blog!
      </Button>
    </form>
  )
}

export default NewBlogForm