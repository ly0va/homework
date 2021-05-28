import blogService from '../services/blogs'
const initialState = []


const getBlogsAction = (blogs) => {
  return {
    type: 'GET_BLOGS',
    blogs
  }
}

const createBlogAction = (newBlog) => {
  return {
    type: 'CREATE_BLOG',
    newBlog
  }
}

const sortBlogsAction = () => {
  return {
    type: 'SORT_BLOGS'
  }
}

const likeBlogAction = (blogToLike) => {
  return {
    type: 'LIKE_BLOG',
    blogToLike
  }
}

const addCommentAction = (comment) => {
  return {
    type: 'ADD_COMMENT',
    comment
  }
}


const removeBlogAction = (blogToRemove) => {
  return {
    type: 'REMOVE_BLOG',
    blogToRemove
  }
}

const removeBlogFromState = (allBlogs, blogToRemove) => {
  return allBlogs.filter(blog => {
    return blogToRemove.id !== blog.id
  })
}

const addCommentToState = (allBlogs, comment) => {
  console.log('Comment', comment, 'blogs', allBlogs)
  const blog = allBlogs.find(blog =>
    blog.id === comment.blog
  )
  const updatedBlog = {
    ...blog,
    comments: blog.comments.concat(comment)
  }
  return allBlogs.map(blog =>
    (blog.id === comment.blog)
      ? updatedBlog
      : blog
  )
}

export const removeBlog = (blogToRemove) => {
  return async (dispatch) => {
    try {
      if (window.confirm(`Do you really want to delete '${blogToRemove.title}'?`)) {
        await blogService.deleteBlog(blogToRemove)
        dispatch(removeBlogAction(blogToRemove))
      }
    }
    catch (exception) {
      console.log(exception)
    }
  }
}

const likeBlog = (allBlogs, updatedBlog)  => {
  const index = allBlogs.findIndex(
    blog =>
    {
      return blog.id.toString() === updatedBlog.id.toString()
    }
  )
  const stateCopy = [...allBlogs]
  stateCopy[index] = updatedBlog
  return stateCopy
}

export const sortBlogs = () => {
  return dispatch => {
    dispatch(sortBlogsAction())
  }
}

export const likeBlogAndSort = (blogToLike) => {
  return async (dispatch) => {
    blogToLike = {
      ...blogToLike,
      comments: blogToLike.comments.map (comment => comment.id)
    }
    const updatedBlog = await blogService.likeBlog(blogToLike)
    dispatch(likeBlogAction(updatedBlog))
    dispatch(sortBlogs())
  }
}

export const getBlogs = () => {
  return async dispatch => {
    const blogs = await blogService.getAll()
    dispatch(getBlogsAction(blogs))
  }
}

export const createBlog = (newBlog) => {
  return async dispatch => {
    let blogFromDB = await blogService.createBlog(newBlog)
    // add username so that it displays on screen after creation
    blogFromDB = {
      ...blogFromDB,
      user: {
        name: newBlog.user.name
      }
    }
    dispatch(createBlogAction(blogFromDB))
  }
}

export const addComment = (comment, id) => {
  return async dispatch => {
    const returnedComment = await blogService.addComment(comment, id)
    dispatch(addCommentAction(returnedComment))
  }
}

// TODO: implement ADD_COMMENT & move async request to thunk
const blogsReducer = (state = initialState, action) => {
  switch (action.type) {
    case 'GET_BLOGS':
      return action.blogs
    case 'CREATE_BLOG':
      return state.concat(action.newBlog)
    case 'SORT_BLOGS': {
      const stateCopy = [...state]
      return stateCopy.sort((a, b) => - a.likes + b.likes)
    }
    case 'LIKE_BLOG': {
      return likeBlog(state, action.blogToLike)
    }
    case 'REMOVE_BLOG': {
      return removeBlogFromState(state, action.blogToRemove)
    }
    case 'ADD_COMMENT': {
      return addCommentToState(state, action.comment)
    }
    default:
      return state
  }
}

export default blogsReducer