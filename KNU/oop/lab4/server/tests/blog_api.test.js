const mongoose = require ('mongoose')
const supertest = require ('supertest')
//const bcrypt = require ('bcrypt')
// const jwt = require ('jsonwebtoken')
const app = require ('../app')
const Blog = require ('../models/blog')
const User = require('../models/user')
const helper = require ('./test_helper')
const api = supertest(app)


const login = async () => {
  const response = await api
    .post('/api/login')
    .send({
      ...helper.initialUser,
      password: helper.initialUserPassword
    })
    .expect(200)
    .expect('Content-Type', /application\/json/)
  return response.body
}

beforeEach(async () => {
  await Blog.deleteMany({})

  for (let blog of helper.initialBlogs) {
    let blogObject = new Blog(blog)
    await blogObject.save()
  }

  await User.deleteMany({})
  const newUser = new User(helper.initialUser)
  await newUser.save()
})

describe ('GET request tests', () => {
  test('GET request returns data in json', async () => {
    const blogsInDB = await api
      .get('/api/blogs')
      .expect(200)
      .expect('Content-Type', /application\/json/)
    expect(blogsInDB.body).toHaveLength(helper.initialBlogs.length)
  })

  test('a specific blog is within the returned blogs', async() => {
    const response = await api.get('/api/blogs')

    const expectedTitle = helper.initialBlogs[1].title

    const titles = response.body.map(blog => blog.title)
    expect(titles).toContain(expectedTitle)
  })

  test('blog object has property \'id\' instead of \'_id\'', async () => {
    const response = await api.get('/api/blogs')
    expect(response.body[0].id).toBeDefined()
  })
})

describe ('POST request tests', () => {
  test('POST request adds the new blog to the DB', async () => {
    const response = await login()

    const newBlog = {
      author: '123',
      title: '234',
      likes: 123,
      url: 'qwe',
    }
    await api
      .post('/api/blogs')
      .set('Authorization', `Bearer ${response.token}`)
      .send(newBlog)
      .expect(201)
      .expect('Content-Type', /application\/json/)

    const blogsAfterInsert = await helper.blogsInDB()

    expect (blogsAfterInsert).toHaveLength(helper.initialBlogs.length + 1)

    const blogsContent = blogsAfterInsert.map( blog => {return {
      author: blog.author,
      title: blog.title,
      url: blog.url,
      likes: blog.likes
    }})
    expect (blogsContent).toContainEqual(newBlog)
  })

  test('if likes property is missing, it defaults to 0', async () => {
    const response = await login()

    const newBlog = {
      author: 'test',
      title: 'test article',
      url: 'localhost'
    }
    await api
      .post('/api/blogs')
      .set('Authorization', `Bearer ${response.token}`)
      .send(newBlog)
      .expect(201)
      .expect('Content-Type', /application\/json/)

    const blogsInDB = await helper.blogsInDB()

    const processedNewBlog = blogsInDB.find((blog) => {
      return blog.title === 'test article'
    })

    expect(processedNewBlog.likes).toBeDefined()
    expect(processedNewBlog.likes).toEqual(0)
  })

  test('if title/url is missing, return status code 400', async () => {
    const response = await login()

    const badBlog = {
      author: 'test',
      likes: 100
    }
    await api
      .post('/api/blogs')
      .set('Authorization', `Bearer ${response.token}`)
      .send(badBlog)
      .expect(400)
  })

  test ('if JWT token isn\'t provided, status code 401 is returned', async () => {
    const newBlog = {
      author: '123',
      title: '234',
      likes: 123,
      url: 'qwe',
    }

    await api
      .post('/api/blogs')
      .set('Authorization', 'Bearer  ')
      .send(newBlog)
      .expect(401)

    await api
      .post('/api/blogs')
      .set('Authorization', '')
      .send(newBlog)
      .expect(401)

    await api
      .post('/api/blogs')
      .send(newBlog)
      .expect(401)
  })
})


describe ('PUT request tests', () => {
  test ('PUT request with invalid id returns 400', async () => {
    const invalidID  = 'dfkasdjfhkajsdhf'

    await api
      .put(`/api/blogs/${invalidID}`)
      .expect(400)
  })

  test ('PUT request with nonexistant id returns 404', async () => {
    const nonexistantID = helper.nonexistingId()

    await api
      .put(`/api/blogs/${nonexistantID}`)
      .expect(404)
  })
})

describe ('user creation', () => {

  test ('creation succeeds with a new username', async () => {
    const usersAtStart = await helper.usersInDB()

    const newUser = {
      username: 'mluuk',
      password: 'salainen',
      name: 'matti'
    }

    await api
      .post('/api/users')
      .send(newUser)
      .expect(200)
      .expect('Content-Type', /application\/json/)

    const usersAtEnd = await helper.usersInDB()
    expect(usersAtEnd).toHaveLength(usersAtStart.length + 1)

    const usernames = usersAtEnd.map (user => user.username)
    expect(usernames).toContain(newUser.username)
  })

  test ('creation with username that is already in DB fails', async () => {
    const usersAtStart = await helper.usersInDB()
    const newUser = {
      username: usersAtStart[0].username,
      password: 'xasdfad',
      name: 'test'
    }

    const result = await api
      .post('/api/users')
      .send(newUser)
      .expect(400)
      .expect('Content-Type', /application\/json/)

    expect(result.body.error).toContain('`username` to be unique')

    const usersAtEnd = await helper.usersInDB()
    expect(usersAtEnd).toHaveLength(usersAtStart.length)
  })

  test ('creation with username that is less then 3 chars long fails', async () => {
    const usersAtStart = await helper.usersInDB()

    const newUser = {
      username: 'xd',
      password: 'xasdfad',
      name: 'test'
    }

    const result = await api
      .post('/api/users')
      .send(newUser)
      .expect(400)
      .expect('Content-Type', /application\/json/)


    expect(result.body.error).toContain('`username`')
    expect(result.body.error).toContain('is shorter than the minimum allowed length')

    const usersAtEnd = await helper.usersInDB()
    expect(usersAtEnd).toHaveLength(usersAtStart.length)
  })

  test ('creation with password that is less then 3 chars long fails', async () => {
    const usersAtStart = await helper.usersInDB()

    const newUser = {
      username: 'asdfasdfasdgasgas',
      password: 'xd',
      name: 'test'
    }

    const result = await api
      .post('/api/users')
      .send(newUser)
      .expect(400)
      .expect('Content-Type', /application\/json/)


    expect(result.body.error).toContain('password is too short')

    const usersAtEnd = await helper.usersInDB()
    expect(usersAtEnd).toHaveLength(usersAtStart.length)
  })

  test ('creation with no username fails', async () => {
    const usersAtStart = await helper.usersInDB()

    const newUser = {
      password: 'xdasdfasdf',
      name: 'test'
    }

    const result = await api
      .post('/api/users')
      .send(newUser)
      .expect(400)
      .expect('Content-Type', /application\/json/)

    expect(result.body.error).toContain('Path `username` is required')

    const usersAtEnd = await helper.usersInDB()
    expect(usersAtEnd).toHaveLength(usersAtStart.length)
  })

  test ('creation with no password fails', async () => {
    const usersAtStart = await helper.usersInDB()

    const newUser = {
      username: 'asldfjasdlf',
      name: 'test'
    }

    const result = await api
      .post('/api/users')
      .send(newUser)
      .expect(400)
      .expect('Content-Type', /application\/json/)

    expect(result.body.error).toContain('password is too short')

    const usersAtEnd = await helper.usersInDB()
    expect(usersAtEnd).toHaveLength(usersAtStart.length)
  })

  /*
  test ('creating a blog results in a cross-reference between a blog and a user', async () => {
    const newBlog = {
      title: 'test blog',
      author: 'me',
      url: 'local',
      likes: 10
    }
    await api
      .post('/api/blogs')
      .send(newBlog)
      .expect(201)
      .expect('Content-Type', /application\/json/)

    const usersAtEnd = await helper.usersInDB()
    const blogsAtEnd = await helper.blogsInDB()

    expect (usersAtEnd)
  })
  */
})

describe ('login tests', () => {

  test ('logging in with correct log/pass returns a JWT', async () => {
    const newUser = {
      username: helper.initialUser.username,
      password: helper.initialUserPassword
    }
    const result = await api
      .post('/api/login')
      .send(newUser)
      .expect(200)

    expect(result.body).toHaveProperty('token')
  })
})
afterAll(() => {
  mongoose.connection.close()
})
