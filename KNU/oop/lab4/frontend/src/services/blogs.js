import axios from 'axios'
const baseUrl = '/api/blogs'

let token = null

const setToken = (newToken) =>
{
  if (newToken === null)
  {
    token = null
  }
  else
  {
    token = `bearer ${newToken}`
  }
}

const getAll = async () =>
{
  const response = await axios.get(baseUrl)
  return response.data
}

const likeBlog = async (blogToUpdate) =>
{
  try
  {
    const newBlog =
    {
      ...blogToUpdate,
      likes: blogToUpdate.likes + 1,
      user: blogToUpdate.user.id
    }
    const response = await axios.put(
      `${baseUrl}/${blogToUpdate.id}`
      , newBlog
      , {
        headers:
        {
          'content-type': 'application/json'
        }
      }
    )
    return response.data
  }
  catch (exception)
  {
    console.log(exception.response.data.error)
  }
}

const addComment = async (comment, id) => {
  try {
    console.log(`${baseUrl}/${id}/comments`)
    const response = await axios.post (
      `${baseUrl}/${id}/comments`,
      comment
    )
    return response.data
  }
  catch (exception) {
    console.log(exception)
  }
}

const createBlog = async (newBlog) =>
{
  try {
    const config = {
      headers: { Authorization: token }
    }
    const response =  await axios.post(baseUrl, newBlog, config)
    return response.data
  }
  catch (exception) {
    console.log(exception)
  }
}

const deleteBlog = async (blogToRemove) =>
{
  try
  {
    const config = { headers: { Authorization: token } }
    await axios.delete (
      `${baseUrl}/${blogToRemove.id}`,
      config
    )
  }
  catch (exception)
  {
    console.log(exception.response.data.error)
    throw exception.response.data.error
  }

}

export default
{
  getAll,
  createBlog,
  likeBlog,
  setToken,
  deleteBlog,
  addComment
}