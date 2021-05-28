import React from 'react'
import {useSelector} from 'react-redux'
import Blog from './Blog'
import  {
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableRow,
  Paper,
  Typography
} from '@material-ui/core'

// dispatching actions that change the state causes components to re-render
const Blogs = () =>
{
  const blogs = useSelector(state => state.blogs)

  return (
    <TableContainer component = {Paper}>
      <Table id = 'blogs'>
        <TableBody>
          <TableRow>
            <TableCell>
              <Typography variant="h6">
                Blog name
              </Typography>
            </TableCell>
            <TableCell>
              <Typography variant="h6">
                Blog author
              </Typography>
            </TableCell>
          </TableRow>
          {
            blogs.map(blog =>
              <TableRow key = {blog.id}>
                <Blog
                  key={blog.id}
                  blog={blog}
                />
              </TableRow>
            )
          }
        </TableBody>
      </Table>
    </TableContainer>
  )
}

export default Blogs