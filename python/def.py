#
# call-by-object
# Don't forget to put colon, ':'.
#
def times(x, y):
	return x * y
#
# *args : arbitrary arguments(variadic)
#
def concat(*args, sep="/"):
	print('type : {}'.format(type(args)))	# Note that args is a tuple
	return sep.join(args)

#
# **kwargs(keyword arguements): arbitrary arguments
#
def table(**kwargs):
	print('type : {}'.format(type(kwargs)))	# Note that kwargs is a dict.
	for name, value in kwargs.items():
		print('{0}: {1}'.format(name, value))

print(times(10, 20))
print(concat("earth", "mars", "venus"))
table(apple = 'fruit', cabbage = 'vegetables')

#
# Unpacking
#
var = [3, 10]
print(list(range(*var)))