#
# Python supports while-else and for-else statement
# which runs if and only if the loop exited normally.
#
a, b = 0, 10
while a < b:
	print(a, end=' ')
	a += 1
else:
	print('\nwhile-loop is done successfully!')

for a in ['Blizzard', 'Hearth Stone', 'Diablo', 'Starcraft', 'Overwatch']:
	print(a, end=' ')
else:
	print('\nfor-loop is done successfully!')

list_one = ['Blizzard', 'Hearth Stone', 'Diablo', 'Starcraft', 'Overwatch']
list_two = ['Klei', 'Don\'t starve', 'Oxygen not included']
for x, y in zip(list_one, list_two):
	print(x.center(21, ' '), end='|')
	print(y.center(21, ' '))

#
# enumerate(sequence, start=0)
# *returns a tuple* containing a count and the value
#
seasons = ['Sprint', 'Summer', 'Fall', 'Winter']
for num, name in enumerate(seasons):
	print(num, name)

#
# In Python, the while-loop & for-loop works on
# any 'iterable ojbects', or 'iterable'.
# With 'iterator' objects, any loop can be performed.
#
iterable_object = [1, 2, 3, 4]
iterator = iter(iterable_object)

# print(next(iterable_object))		TypeError: 'list' object is not an iterator
print(next(iterator))
print(next(iterator))
print(next(iterator))
print(next(iterator))
# print(next(iterator))				It raises 'StopIteration'.


#
# Manual iteration
# e.g)
#
# temp = [1, 2, 3]
# for x in temp:
# 	print(x ** 2, end=' ')
#
temp = [1, 2, 3]
i = iter(temp)
while True:
	try:
		x = next(i)
	except StopIteration:
		break
	print(x ** 2, end=' ')

#
# Generator Function
# Generator Expression
#
# The keyword 'yield' is used like 'return',
# but it will return a generator, a lazy pending list object.
# Printing a string before and after yield statement
# will elaborate this idea.
#
# It is always smart to use yield
# when you don't need to read
# the whole data at once.
#
print('\n')
def createGenerator():
	mylist = range(3)
	for i in mylist:
		print('before yield')
		yield i*i
		print('after yield')

generator = createGenerator()
print(generator)
for i in generator:
	print(i)
	print('=' * 10)

generator = createGenerator()
iterator = iter(generator)
print('=' * 10)
print(next(iterator))
print('=' * 10)
print(next(iterator))
print('=' * 10)
print(next(iterator))

#
# Another example of generator
#
def integers():
	i = 1
	while True:	# infinite loop
		yield i	# yield
		i += 1

def squares():
	for i in integers():
		yield i*i	#yield

def take(n, seq):
	seq = iter(seq)
	result = []
	try:
		for i in range(n):
			result.append(next(seq))
	except StopIteration:
		pass
	return result

print(take(5, squares()))

#
# Generator expression
# Enclosed in parentheses.
#
ge = (c * 4 for c in 'SPAM')
print(ge)			# Generator object , made with generator expression.
print(list(ge))		# It works, generates, at this time.