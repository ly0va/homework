const totalLikes = require ('../utils/list_helper').totalLikes

describe('totalLikes', () => {
  test('of empty list is zero', () => {
    const blogs = []
    expect(totalLikes(blogs)).toBe(0)
  })

  test ('when list had only one blog equals the likes of that', () => {
    const blogs = [
      {
        _id: '5a422aa71b54a676234d17f8',
        title: '10 reasons why you should get a job',
        author: 'Your conscience',
        url: 'yourbrain.com',
        likes: 1,
        __v: 0
      }
    ]
    expect(totalLikes(blogs)).toBe(1)
  })

  test ('of a bigger list is calculated right', () => {
    const blogs = [
      {
        _id: '5a422aa71b54a676234d17f8',
        title: '10 reasons why you should get a job',
        author: 'Your conscience',
        url: 'yourbrain.com',
        likes: 1,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'Problems are opportunities',
        author: 'Tina Silig',
        url: 'yourpurpose.com',
        likes: 2,
        __v: 0
      },
      {
        _id: '5a422aa71b54a676234d17f8',
        title: 'The solution to your problems are where you haven\'t looked yet',
        author: 'Jordan Peterson',
        url: 'lifeadvice.com',
        likes: 2,
        __v: 0
      }
    ]

    expect(totalLikes(blogs)).toBe(5)
  })
})
