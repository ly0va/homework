import React from 'react'
import {TextField} from '@material-ui/core'

const LoginPassword = ({ password, handlePasswordChange }) => (
  <TextField
    type = 'password'
    id = 'loginPasswordInput'
    value = {password}
    name = "Password"
    onChange = {handlePasswordChange}
    label="password"
    autoComplete = "current-password"
  >
  </TextField>
)

export default LoginPassword