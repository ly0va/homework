import React, { useEffect, useRef } from 'react'
import { useSelector, useDispatch } from 'react-redux'
import { Switch, Route, useRouteMatch } from 'react-router-dom'


import Blogs from './components/Blogs'
import Login from './components/Login'
import NewBlogForm from './components/NewBlogForm'
import Notification from './components/Notification'
import Togglable from './components/Togglable'
import Users from './components/Users'
import User from './components/User'
import Blog from './components/Blog'
import Navigation from './components/Navigation'
import Container from '@material-ui/core/Container'

import blogService from './services/blogs'
import { setNotification } from './reducers/NotificationReducer'
import { createBlog, getBlogs, sortBlogs } from './reducers/BlogsReducer'
import { setUser } from './reducers/UserReducer'
import { getAllUsers } from './reducers/AllUsersReducer'



const App = () =>
{
  const matchUser = useRouteMatch('/users/:id')
  const matchBlog = useRouteMatch('/blogs/:id')
  const user = useSelector(state => state.user)
  const notification = useSelector(state => state.notification)
  const users = useSelector(state => state.users)
  const blogs = useSelector(state => state.blogs)
  const dispatch = useDispatch()


  const userToShow = matchUser
    ? users.find(user =>
    {
      return user.id === matchUser.params.id
    })
    : null

  const blogToShow = matchBlog
    ? blogs.find(blog => blog.id === matchBlog.params.id)
    : null


  useEffect(() =>
  {
    async function fetchUsers()
    {
      await dispatch(getAllUsers())
    }
    fetchUsers()
  }, [])


  useEffect(() =>
  {
    async function fetchData()
    {
      await dispatch(getBlogs())
      dispatch(sortBlogs())
    }
    fetchData()
  }, [])

  useEffect(() =>
  {
    const loggedUserJSON = window.localStorage.getItem(
      'loggedBlogappUser'
    )
    if (loggedUserJSON) {
      const user = JSON.parse(loggedUserJSON)
      dispatch(setUser(user))
      blogService.setToken(user.token)
    }
  }, [])

  const newBlogFormRef = useRef()

  const addBlog = async (newBlog) =>
  {
    const expandedBlog = {
      ...newBlog,
      user: {
        name: user.name
      }
    }
    await dispatch(createBlog(expandedBlog))
    dispatch(setNotification({
      content: `a new blog ${expandedBlog.title} by ${expandedBlog.author} added`,
      isGood: true
    }))
    newBlogFormRef.current.toggleVisibility()
  }

  const blogsComponent = (
    <div>
      <Blogs />
      <Togglable buttonText='add new blog!' ref={newBlogFormRef}>
        <NewBlogForm
          addBlog={addBlog}
        />
      </Togglable>
    </div>
  )


  return (
    <Container>
      <div>
        <Notification
          notification={notification}
        />
        <h2 style={{ fontFamily: 'Tangerine, serif' }}>Blogs app</h2>
        {
          user
            ? <>
              <Navigation />
              <Switch>
                <Route path='/users/:id'>
                  <User user={userToShow} />
                </Route>
                <Route path='/users/'>
                  <Users />
                </Route>
                <Route path='/blogs/:id'>
                  <Blog blog={blogToShow} view='oneBlog' />
                </Route>
                <Route path='/'>
                  {
                    user
                      ? blogsComponent
                      : null
                  }
                </Route>
              </Switch>
            </>
            : <Login />
        }
      </div>
    </Container>
  )
}

export default App