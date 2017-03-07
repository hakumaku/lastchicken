"""
Decorator function
Decorator class
"""

def decorator_function(original_function):

	def wrapper_function(*args, **kwargs):
		print 'wrapper executed this before %s' % original_function.__name__
		return original_function(*args, **kwargs)

	return wrapper_function

class decorator_class(object):

	def __init__(self, original_function):
		self.original_function = original_function

	def __call__(self, *args, **kwargs):
		print 'call method this before %s' % self.original_function.__name__
		return self.original_function(*args, **kwargs)

def my_logger(orig_func):
	import logging
	logging.basicConfig(filename='{}.log'.format(orig_func.__name__), level=logging.INFO)

	def wrapper(*args, **kwargs):
		logging.info(
			'Ran with args: {}, and kwargs: {}'.format(args, kwargs))
		return orig_func(*args, **kwargs)

	return wrapper

def my_timer(orig_func):
	import time

	def wrapper(*args, **kwargs):
		t1 = time.time()
		result = orig_func(*args, **kwargs)
		t2 = time.time() - t1
		print('{} ran in: {} sec'.format(orig_func.__name__, t2))

	return wrapper

# This sysntax is the same with
# 'display = decorator_function(display)'
hide = True
if hide:
	@my_logger
	@my_timer
	def display_info(name, age):
		print 'display_info ran with arguments (%s, %s)' % (name, age)
"""
The top decorator gets ran at last
display_info = my_logger(my_timer(display_info))
"""
	display_info('Jone', 25)

else:
	@decorator_function
	def display():
		print('display function ran')

	@decorator_class
	def display_info(name, age):
		print 'display_info ran with arguments (%s, %s)' % (name, age)

	display()
	display_info('Jone', 25)