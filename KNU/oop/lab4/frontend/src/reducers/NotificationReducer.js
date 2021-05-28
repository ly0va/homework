const initialState = {
  content: null,
  isGood: false
}

const setNotificationAction = (notification) => {
  return {
    type: 'SET_NOTIFICATION',
    content: notification.content,
    isGood: notification.isGood
  }
}

export const setNotification = (notification) => {
  return dispatch => {
    dispatch(setNotificationAction(notification))
    setTimeout(() => dispatch(setNotificationAction({
      content: null,
      isGood: false
    })), 5000)
  }
}

const notificationReducer =  (state = initialState, action) => {
  switch (action.type) {
    case 'SET_NOTIFICATION':
      return {
        content: action.content,
        isGood: action.isGood
      }
    default:
      return state
  }
}

export default notificationReducer