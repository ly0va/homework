import React from 'react'
import {TextField} from '@material-ui/core'

const LoginUsername = ({ username, handleUsernameChange }) =>
{
  return (<TextField
    type = 'text'
    id = 'loginUsernameInput'
    value = {username}
    name = 'Username'
    onChange = {handleUsernameChange}
    label = 'username'
    autoComplete = "username"
  >

  </TextField>)
}
export default LoginUsername