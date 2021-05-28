import React, { useState, useImperativeHandle } from 'react'
import PropTypes from 'prop-types'
import {Button} from '@material-ui/core'

const Togglable = React.forwardRef((props, ref) =>
{
  const [isVisible, setIsVisible] = useState (false)

  const toggleVisibility = () =>
  {
    setIsVisible(!isVisible)
  }

  const hideWhenVisible = { display: isVisible ? 'none' : '' }
  const showWhenVisible = { display: isVisible ? '' : 'none' }

  useImperativeHandle(ref, () =>
  {
    return {
      toggleVisibility
    }
  })
  return (
    <div>
      <div style = {hideWhenVisible}>
        <Button variant="contained"
          onClick = {toggleVisibility}
        >
          {props.buttonText}
        </Button>
      </div>
      <div style = {showWhenVisible}>
        {props.children}
        <Button variant="contained"
          onClick = {toggleVisibility}
        >
          cancel
        </Button>
      </div>
    </div>
  )
})

Togglable.displayName = 'Togglable'

Togglable.propTypes = {
  buttonText: PropTypes.string.isRequired
}

export default Togglable