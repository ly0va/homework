#!/usr/bin/python3

import os
import pickle
import matplotlib.pyplot as plt
from collections import defaultdict

sizes = defaultdict(int)

if os.path.exists('./sizes.pkl'):
    with open('./sizes.pkl', 'rb') as jar:
        sizes = pickle.load(jar)
        print('read from cache')
else:
    print('collecting data')
    for dirname, dirs, files in os.walk('/home/redboot/'):
        for filename in files:
            try:
                size = os.stat(f'{dirname}/{filename}').st_size
                sizes[size] += 1
            except OSError:
                pass
    with open('sizes.pkl', 'wb') as jar:
        pickle.dump(sizes, jar)
        print('data saved to ./sizes.pkl')

powers = defaultdict(int)
n = sum(sizes.values())
files = [(k, v) for k, v in sizes.items()]
files.sort()

c = 0
for k, v in files:
    c += v
    if c >= 0.75*n:
        break

print('75% of files are not larger than', k)
print('Total files:', n)
print('Total size:', sum(k*v for k, v in sizes.items()))

for k, v in sizes.items():
    powers[len(bin(k))-2] += v


plt.bar([*powers.keys()], [*powers.values()])
plt.xticks(range(max(powers.keys())))
plt.ylabel('number of files')
plt.xlabel('log(size of files)')
plt.show()




