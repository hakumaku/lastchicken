list_one = [12, 23, 'efgh', 'abcd']
list_two = ['ab', 'cd', 'ef', 'gh', 'ij']

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
# Invalid Syntax: list_one[4] = 'xyz'
# Instead, use list.append()
#
print('\nlist.append()')
list_one.append('xyz')
print(list_one)