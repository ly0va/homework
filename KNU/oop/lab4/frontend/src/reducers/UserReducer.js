import loginService from '../services/login'
import blogService from '../services/blogs'
import {setNotification} from './NotificationReducer'

const initialState = null

/* TODO: add action handler for changing user data
   & async thunk for login requet to server
*/

export const setUser = (userData) => {
  return {
    type: 'SET_USER',
    userData
  }
}

export const login = (username, password) => {
  return async dispatch => {
    try
    {
      const userData = await loginService
        .login({ username, password })

      if (userData)
      {
        window.localStorage.setItem(
          'loggedBlogappUser',
          JSON.stringify(userData)
        )
        blogService.setToken(userData.token)
        console.log(`logging in with ${username} ${password}`)
        dispatch(setUser(userData))
      }
    }
    catch (exception) {
      dispatch(setNotification({
        content: 'Failed to login! Wrong username or password',
        isGood: false
      }))
      console.log (`Wrong credentials ${exception}`)
    }
  }
}

const userReducer = (state = initialState, action) => {
  switch (action.type) {
    case 'SET_USER': {
      return action.userData
    }
    default:
      return state
  }
}

export default userReducer