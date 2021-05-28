import userService from '../services/users'
const initialState = []

const getAllUsersAction = (users) => {
  return {
    type: 'GET_ALL_USERS',
    users
  }
}

export const getAllUsers = () => {
  return async dispatch => {
    const users = await userService.getUsers()
    dispatch(getAllUsersAction(users))
  }
}

const allUsersReducer = (state = initialState, action) => {
  switch (action.type) {
    case 'GET_ALL_USERS': {
      return action.users
    }
    default:
      return state
  }
}

export default allUsersReducer