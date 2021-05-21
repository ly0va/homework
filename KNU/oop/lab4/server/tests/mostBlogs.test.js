const mostBlogs = require ('../utils/list_helper').mostBlogs

describe('most blogs', () => {
  test('with zero blogs given', () => {
    const blogs = []
    expect(mostBlogs(blogs)).toBeNull()
  })

  test('with 1 blog', () => {
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
    const expectedResult =
    {
      author: 'Laurie Santos',
      blogs: 1
    }
    expect(mostBlogs(blogs)).toEqual(expectedResult)
  })

  test('with 3 blogs (2+1)', () => {
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
        author: 'me',
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
      blogs: 2
    }
    expect(mostBlogs(blogs)).toEqual(expectedResult)
  })
})