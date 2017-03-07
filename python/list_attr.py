list_one = [12, 23, 'efgh', 'abcd']
list_two = ['ab', 'cd', 'ef', 'gh', 'ij']
list_nest=[
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 9]
]

#
# Changing an element in a list.
#
list_one[1] = 34
print('{}\n'.format(list_one))

#
# Slicing
#
print('Slicing...')
print(list_one[0])
print(list_one[-1])	# The last character
print(list_one[:3])	# from beg to [2], not [3].
print(list_one[1:])	# from [1] to the last.

#
# You can use 'del' statement or list.remove()
#
print('del & list.remove()')
print('Original: {}'.format(list_two))
del list_two[0]
list_two.remove('cd')
print('Deletion: {}'.format(list_two))

#
# Way better use list.pop(index)
#
print('\nlist.pop() ({})'.format(list_one))
list_one.pop(1)
print(list_one)

#
# Invalid Syntax: list_one[4] = 'xyz'
# Instead, use list.append()
#
print('\nlist.append()')
list_one.append('xyz')
print(list_one)

#
# list.extend(list)
# list.insert(index, value)
#
print('\nlist.extend() & list.insert()')
list_one.extend([1, 2, 3])
print(list_one)
list_one.insert(0, 'pqrst')
print(list_one)

#
# Beware of reference and copy
#
temp = [1, 2, 3]
list_one = ['a', temp, 'c']		# reference
list_two = ['a', temp[:], 'c']	# copy
print('\nShallow copy & deep copy')
print(list_one, list_two)
print('Is list_one[1] list_two[1]?? : {}'.format(list_one[1] is list_two[1]))
temp[1] = 5						# affects list_one, but not list_two
print(list_one, list_two)

#
# Can make a nested list
# temp_nested = temp[:] makes sense, but not *Pythonic*.
# Much better use list(temp)
#
temp_nested = list(temp)
temp = temp * 3
temp_nested = [temp_nested] * 3
print('temp : {}'.format(temp))					# [a,b,c, ... ,a,b,c]
print('temp_nested : {}'.format(temp_nested))	# [[a,b,c], ... , [a,b,c]]