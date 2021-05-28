import React from 'react'
import { useSelector } from 'react-redux'
import { Link } from 'react-router-dom'

import  {
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableRow,
  Paper,
  Typography
} from '@material-ui/core'

const Users = () => {
  const users = useSelector(state => state.users)

  return (
    <div>
      <p>
        <Typography variant = 'h4'> Users </Typography>
      </p>
      <TableContainer component = {Paper}>
        <Table>
          <TableBody>
            <TableRow>
              <TableCell>
                <Typography variant = 'h6'>  Username </Typography>
              </TableCell>
              <TableCell>
                <Typography variant = 'h6'> Blogs created </Typography>
              </TableCell>
            </TableRow>
            {users.map(user => {
              return (
                <TableRow key = {user.id}>
                  <TableCell>
                    <Link to = {`/users/${user.id}`}> {user.name} </Link>
                  </TableCell>
                  <TableCell>
                    {user.blogs.length}
                  </TableCell>
                </TableRow>
              )
            })}
          </TableBody>
        </Table>
      </TableContainer>
    </div>
  )
}

export default Users