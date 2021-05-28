import React from 'react'

const Comments = ({comments}) => {
  return (
    <div>
      <ul>
        {
          comments.map(comment =>
            <li key = {comment.id}> {comment.content} </li>
          )
        }
      </ul>
    </div>
  )
}

export default Comments