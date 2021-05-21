const favouriteBlog = require ('../utils/list_helper').favouriteBlog

describe('favourite blog', () => {
  test('is null when no blogs are given', () => {
    const blogs = []
    expect(favouriteBlog(blogs)).toBeNull()
  })

  test('with 1 blog given', () => {
    const blogs =
    [
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'Social media are harmful',
        author: 'Laurie Santos',
        url: 'coursera.org',
        likes: 100,
        __v: 0
      }
    ]
    const expectedBlog =
    {
      title: 'Social media are harmful',
      author: 'Laurie Santos',
      likes: 100,
    }
    expect(favouriteBlog(blogs)).toEqual(expectedBlog)
  })

  test('with 3 blogs given', () => {
    const blogs =
    [
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'Social media are harmful',
        author: 'Laurie Santos',
        url: 'coursera.org',
        likes: 100,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'Stop using your phone so much',
        author: 'common sense',
        url: 'localhost',
        likes: 5,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'You are a beatiful person',
        author: 'me',
        url: 'localhost',
        likes: 10000,
        __v: 0
      }
    ]

    const expectedBlog =
    {
      title: 'You are a beatiful person',
      author: 'me',
      likes: 10000
    }

    expect(favouriteBlog(blogs)).toEqual(expectedBlog)
  })

  test('doesn\'t crash if multiple blogs have same amount of likes', () => {
    const blogs =
    [
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'Social media are harmful',
        author: 'Laurie Santos',
        url: 'coursera.org',
        likes: 100,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'Stop using your phone so much',
        author: 'common sense',
        url: 'localhost',
        likes: 100,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'You are a beatiful person',
        author: 'me',
        url: 'localhost',
        likes: 100,
        __v: 0
      }
    ]
    const expectedBlog =
    {
      title: 'Social media are harmful',
      author: 'Laurie Santos',
      likes: 100
    }

    expect(favouriteBlog(blogs)).toEqual(expectedBlog)
  })
})