"""
	1) Keys must be immutable.
	2) No duplicate keys are allowed.
"""

dict_one = {
	'name': 'zara',
	'age': 7,
	'class': 'First'
}
dict_two = {
	'major': 'computer science',
	'grade': 'senior'
}
dict_three = {
	'one': 1,
	'two': 2,
	'three': 3,
	'four': 4,
	'five': 5,
	'six': 6
}

print(dict_one['name'])
print(dict_one['age'])
print(dict_one['class'])

#
# Updating & Adding & deleting
#
dict_one['name']	= 'Ariana'	# Updating
dict_one['school']	= 'Hanyang'	# Adding
del dict_one['age']
print('\n{}'.format(dict_one['name']))
print(dict_one['school'])
print(dict_one.keys())

#
# dict.pop(key, default)
# dict.popitem()
#
print('\ndict.pop() & dict.popitem()')
print(dict_one)
dict_one.pop('name')
print(dict_one)
dict_one.pop('name', 'gender')
print(dict_one)
print(dict_three)
dict_three.popitem()
print(dict_three)
dict_three.popitem()
print(dict_three)

#
# dict.get(key, deafault=None)
# Better use this to retreive a value.
# Returns default, if not exists.
#
print('\n{}'.format(dict_one.get('school')))
print(dict_one.get('university'))
print(dict_one.get('university', 'high school'))

#
# dict.items()
# dict.keys()
# dict.values()
#
print('\n{}'.format(dict_one.items()))
print(dict_one.keys())
print(dict_one.values())

#
# dict.update()
#
dict_one.update({'university': 'lion'})
print('\n{}'.format(dict_one.items()))
dict_one.update(dict_two)
print(dict_one.items())
dict_one.update(last = 'grande')
print(dict_one.items())

#
# dict.clear()
#
dict_one.clear()
print('\ndict.clear() : {}'.format(dict_one))