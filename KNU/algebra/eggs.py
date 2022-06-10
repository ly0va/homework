cache = {}

def throws(f, e):
    if f == 0:
        return 0
    if e == 1:
        return f
    if (f, e) in cache:
        return cache[(f, e)]
 
    cache[(f, e)] = 1 + min(
        max(throws(i - 1, e - 1), throws(f - i, e)) 
        for i in range(1, f + 1)
    )

    return cache[(f, e)]

print(throws(5, 2))



