a, b = 2, 3
print('{}'.format(a + b))
print('{}'.format(a - b))
print('{}'.format(a * b))
print('{}'.format(a % b))
print('{:.4f}'.format(a / b))	# division
print('{}'.format(a // b))		# floor division
print('{}'.format(a ** b))		# exponentiation

a **= b		# All the intuitive assignment operators work
print(a)

# The 'in' is a membership operator.
ret = []
for x in range(10):
	ret.append(x)
else:
	print(ret)

a = b = 12
# Identity operator
if a is b:
	print('Yes, a is b')
else:
	print('No, they are different')

# This is NOT identity operator, but equality.
if a == b:
	print('Yes, both a and b are 12')