# Some built-in functions, including type conversion built-in functions.
# They are much faster than what you think.
# Don't hesistate to use them when the situation is suitable.
# print() is also a built-in function.

var = 10			# Number
var2 = '111'		# String

print('hex={}'.format(hex(var)))
print('oct={}'.format(oct(var)))
print('bin={}'.format(bin(var)))

print('hex int({})={}'.format(var2, int(var2, 16)))
print('oct int({})={}'.format(var2, int(var2, 8)))
print('bin int({})={}'.format(var2, int(var2, 2)))

var = -10
print('abs({})={}'.format(var, abs(var)))

a, b, c, d, = range(4)
print('max:{}, min:{}'.format(max(a,b,c,d), min(a,b,c,d)))