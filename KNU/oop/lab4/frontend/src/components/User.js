import React from 'react'

const User = ({user}) => {
  if (!user) {
    return null
  }
  return (
    <>
      <h2> {user.name} </h2>
      <div>
        <h3>added blogs:</h3>
      </div>
      <ul>
        {
          user.blogs.map(
            blog =>
              <div key = {blog.id}>
                <li>
                  {blog.title}
                </li>
              </div>
          )
        }
      </ul>
    </>
  )
}

export default User