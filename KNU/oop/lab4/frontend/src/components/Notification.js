import React from 'react'
import { Alert } from '@material-ui/lab'

const Notification = ({ notification }) =>
{
  if (notification.content === null)
  {
    return null
  }

  return (
    <div>
      {(notification.content &&
        <Alert severity={notification.isGood ? 'success' : 'error'}>
          {notification.content}
        </Alert>
      )}
    </div>
  )
}

export default Notification