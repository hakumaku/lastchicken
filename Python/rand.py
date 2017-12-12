import random

# A random item from a list, tuple, or string.
x = random.choice(range(10))	# 1 ~ 10

# A randomly selected element from range(start, stop, step)
y = random.randrange(1, 10, 2)	# 1,3,5,7,9

print(x, y)

rand_list = [x for x in range(10)]
print(rand_list)
random.shuffle(rand_list)
print(rand_list)