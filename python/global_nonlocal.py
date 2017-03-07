#
# nonlocal & global statement
#
print('Scope'.center(30, '-'))
x = 0				# global

def outer_a():
	x = 1			# outer
	def inner_a():
		x = 2		# inner
		print('inner : ', x)
	inner_a()
	print('outer : ', x)

outer_a()
print('global: ', x)

print('Nonlocal Statement'.center(30, '-'))
x = 0				# global

def outer_b():
	x = 1			# outer
	def inner_b():
		nonlocal x
		x = 2		# inner
		print('inner : ', x)
	inner_b()
	print('outer : ', x)

outer_b()
print('global: ', x)

print('Global Statement'.center(30, '-'))
x = 0				# global

def outer_c():
	x = 1			# outer
	def inner_c():
		global x
		x = 2		# inner
		print('inner : ', x)
	inner_c()	
	print('outer : ', x)

outer_c()
print('global: ', x)