const mostLikes = require ('../utils/list_helper').mostLikes

describe('most likes', () => {
  test('with no blogs', () => {
    const blogs = []
    expect(mostLikes(blogs)).toBeNull()
  })

  test ('with 1 blog', () => {
    const blogs =
    [
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'You are a beatiful person',
        author: 'me',
        url: 'localhost',
        likes: 10000,
        __v: 0
      }
    ]
    const expectedResult =
    {
      author: 'me',
      likes: 10000
    }
    expect(mostLikes(blogs)).toEqual(expectedResult)
  })
  test ('with three blogs (diff authors)', () => {
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
    const expectedResult =
    {
      author: 'me',
      likes: 10000
    }
    expect(mostLikes(blogs)).toEqual(expectedResult)
  })

  test ('with three blogs (all the same author)', () => {
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
        author: 'Laurie Santos',
        url: 'localhost',
        likes: 5,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'You are a beatiful person',
        author: 'Laurie Santos',
        url: 'localhost',
        likes: 10000,
        __v: 0
      }
    ]
    const expectedResult =
    {
      author: 'Laurie Santos',
      likes: 10105
    }
    expect(mostLikes(blogs)).toEqual(expectedResult)
  })

})