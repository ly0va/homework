import { applyMiddleware, createStore, combineReducers } from 'redux'
import {composeWithDevTools} from 'redux-devtools-extension'
import thunk from 'redux-thunk'
import notificationReducer from './reducers/NotificationReducer'
import blogsReducer from './reducers/BlogsReducer'
import userReducer from './reducers/UserReducer'
import allUsersReducer from './reducers/AllUsersReducer'

const reducer = combineReducers({
  blogs: blogsReducer,
  notification: notificationReducer,
  user: userReducer,
  users: allUsersReducer
})

const store = createStore(
  reducer,
  composeWithDevTools(applyMiddleware(thunk))
)

export default store