const logger = require ('./logger')

const tokenExtractor = (request, response, next) => {
  const authorization = request.get('authorization')
  if (authorization && authorization.toLowerCase().startsWith('bearer '))
  {
    request.token = authorization.substring(7)
  } else {
    request.token = null
  }
  next()
}

const requestLogger = (request, response, next) => {
  logger.info('Method:', request.method)
  logger.info('Path:  ', request.path)
  logger.info('Body:  ', request.body)
  logger.info('---')
  next()
}


const unknownEndpoint = (request, response) => {
  logger.info('unknown endpoint!')
  response.status(404).send ({ error: 'unknown endpoint' })
}

const errorHandler = (error, request, response, next) => {
  if (error.name === 'ValidationError') {
    return response.status(400).json({ error: `Validation error: ${error.message}` })
  }
  if (error.name === 'CastError')
  {
    return response.status(400).json({ error: `CastError: ${error.message}` })
  } else if (error.name === 'JsonWebTokenError')
  {
    return response.status(401).json({ error: 'invalid token' })
  }
  response.status(404).send ({ error: `error: ${error.message}` })
  next(error)
}


module.exports = {
  unknownEndpoint,
  errorHandler,
  requestLogger,
  tokenExtractor
}