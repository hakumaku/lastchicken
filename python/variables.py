"""
Python variables do not need explicit declaration unlike C.
	-Numbers
		-int
		-long
		-float
		-complex
	-String
	-List
	-Tuple
	-Dictionary
"""

a = 100			# An interger assignment
b = 1000.0		# A floating point
c = "John"		# A string

# Similar to free() function.
# It is not required all the times, because of garbage collector,
# but in some cases you better use 'del' to explicitly secure space.
del a, b, c

a = b = c = 1

# Pythonic void swap(int x, int y);
a, b, c = 1, 2, "John"
print('a={} b={}'.format(a, b))
a, b = b, a
print('a={} b={}'.format(a, b))

# Strings
# Convention to write in single quotes
string = 'Hello World!'
print(string)
# Slicing
print(string[0])		# print a single character
print(string[2:5])		# print from s[2] to s[4], not s[5]
print(string[-1])		# print s[-1] which is the last character
print(string[2:])		# print from s[2] to the end
print(string[:2])		# print from the beginning to s[1], not s[2]
print(string * 2)		# print s twice
print(string + 'Wow!!')	# Concatenate strings

# Lists
# Similar to arrays in C, but much more flexible.
list_var = ['abcd', 123, 2.23, 'John']
list_var2 = [12, 'edfg']
print(list_var)
# Slicing
print(list_var[0])
print(list_var[1:3])
print(list_var[-1])
print(list_var[1:])
print(list_var[:3])
print(list_var * 2)
print(list_var + list_var2)

# Tuples
# Much like list, but is READ-ONLY, like const type qualifier in C.
tuple_var = ('abcd', 123, 2.23, 'John')
tuple_var2 = (12, 'edfg')
print(tuple_var)
# Slicing
print(tuple_var[0])
print(tuple_var[1:3])
print(tuple_var[-1])
print(tuple_var[1:])
print(tuple_var[:3])
print(tuple_var * 2)
print(tuple_var + tuple_var2)

# Dictionary
# Kind of hash table that you add items with keys.
dict_var = {}
dict_var['one'] = 'This is one'
dict_var['two'] = 'This is two'
dict_var2 = {'name': 'John', 'code': '6734', 'dept': 'sales'}

print('{}'.format(dict_var))
print('{}'.format(dict_var2))
print('{}'.format(dict_var['one']))
print('{}'.format(dict_var2['name']))
print('dict_var keys:{}'.format(dict_var.keys()))
print('dict_var values:{}'.format(dict_var.values()))
print('dict_var2 keys:{}'.format(dict_var2.keys()))
print('dict_var2 values:{}'.format(dict_var2.values()))