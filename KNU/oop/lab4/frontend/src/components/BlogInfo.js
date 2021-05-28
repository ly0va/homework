import React from 'react'
import {useHistory} from 'react-router-dom'
import {useDispatch, useSelector} from 'react-redux'
import { removeBlog, likeBlogAndSort} from '../reducers/BlogsReducer'
import {Button} from '@material-ui/core'

const BlogInfo = ({blog, view}) => {
  const history = useHistory()
  const dispatch = useDispatch ()

  const user = useSelector (state => state.user)

  const removeButtonDisplay = (blog.user.name === user.name)
    ? { display : '' }
    : { display : 'none' }

  const handleRemoveClick = async (blogToRemove) =>
  {
    dispatch(removeBlog(blogToRemove))
    if (view === 'oneBlog') {
      history.push('/')
    }
  }

  const handleLikeClick =  async (blogToUpdate) =>
  {
    dispatch(likeBlogAndSort(blogToUpdate))
  }


  return (
    <div>
      <p>
        URL: <a href = {blog.url}> {blog.url} </a>
      </p>
      <p className = 'blogLikes'>
        Claps: {blog.likes}
        <Button variant="contained"
          onClick = {() => handleLikeClick(blog)}
          className = 'likeButton'
        >
          clap
        </Button>
      </p>
      <p>
        Created by: {blog.user.name}
      </p>
      <Button variant="contained"
        onClick = {() => handleRemoveClick(blog)}
        style = {removeButtonDisplay}
        className = 'removeButton'
      >
        remove
      </Button>
    </div>
  )
}

export default BlogInfo
