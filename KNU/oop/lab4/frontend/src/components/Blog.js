import React from 'react'
import Comments from './Comments'
import BlogInfo from './BlogInfo'
import CommentForm from './CommentForm'
import {Link} from 'react-router-dom'
import  { TableCell } from '@material-ui/core'

const Blog = ({ blog, view }) =>
{
  if (!blog) {
    return null
  }

  return (
    <>
      {
        view === 'oneBlog'
          ?
          <div className = 'blog'>
            <h2> {blog.title} by {blog.author} </h2>
            <BlogInfo blog = {blog} view = {view}/>
            <CommentForm blog = {blog} />
            <Comments comments = {blog.comments}/>
          </div>
          :
          <>
            <TableCell>
              <Link to = {`/blogs/${blog.id}`}>{blog.title} </Link>
            </TableCell>
            <TableCell>
              by {blog.author}
            </TableCell>
          </>
      }
    </>
  )
}

export default Blog
