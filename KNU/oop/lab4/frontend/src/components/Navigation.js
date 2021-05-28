import React from 'react'
import {useDispatch, useSelector} from 'react-redux'

import {Link} from 'react-router-dom'
import {Button} from '@material-ui/core'
import AppBar from '@material-ui/core/AppBar'
import Toolbar from '@material-ui/core/Toolbar'
import Typography from '@material-ui/core/Typography'


import blogService from '../services/blogs'
import {setUser} from '../reducers/UserReducer'

const Navigation = () => {
  const dispatch = useDispatch()
  const user = useSelector (state => state.user)
  const logOut = () =>
  {
    dispatch(setUser(null))
    blogService.setToken(null)
    window.localStorage.removeItem('loggedBlogappUser')
  }

  const navigationStyle = {
    display: 'flex',
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center'
  }

  const userInfoStyle = {
    display: 'flex',
    flexDirection: 'row',
    alignItems: 'center'
  }

  return (
    <div>

      <AppBar position="static">
        <Toolbar style = {navigationStyle}>
          <div>
            <Button color = 'inherit' component = {Link} to="/" >
              home
            </Button>
            <Button color = 'inherit' component = {Link} to="/users" >
              users
            </Button>
          </div>

          <div style = {userInfoStyle}>
            <Typography>
              {user.name} logged in
            </Typography>

            <Button
              type="button"
              onClick = {logOut}
              id = 'logoutButton'
              color = 'inherit'
            >
              logout
            </Button>
          </div>
        </Toolbar>
      </AppBar>

    </div>
  )
}

export default Navigation