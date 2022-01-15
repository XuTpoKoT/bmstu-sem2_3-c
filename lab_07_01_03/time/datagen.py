import sys
from random import randint

if len(sys.argv) == 2:
    size = int(sys.argv[1])
else:
    size = int(input("Size: "))

for i in range(size):
    print(randint(-1000, 1000))
