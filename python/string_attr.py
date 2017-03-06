str_one = 'hello World!'
str_two = 'hello hello hello hello~~'
str_three = 'abcdefg'
str_four = '@@@@Hello World!!@@@@'

#
# Capitalize its first character
#
print('str.capitalize()\n' + str_one.capitalize() + '\n')

#
# Returns a string padded wtih fillchar
# with the original string centered
#
print('str.center() & str.ljust()')
print(str_one.center(30, '*'))
# rjust... do not have ljust?..
print(str_one.rjust(30, '*') + '\n')

#
# Counts how many times str occurs in string
#
print('str.count()')
print(str_two.count('hello', 5))
print(str_two.count('hello', 0, 11))
print(str_two.count('hello', 5, 11))

#
# Similar, but returns its index.
#
print('\nstr.find() & str.rfind() and str.index() & str.rindex()')
print('hello starts at..:{}'.format(str_two.find('hello')))
print('World starts at..:{}'.format(str_one.rfind('World')))

#
# Index & rindex : similar but raises an exception.
#
print('hello starts at..:{}'.format(str_two.index('hello')))
print('World starts at..:{}'.format(str_one.rindex('World')))

#
# startswith & endswith : [suffix, beg(opt), end(opt)]
# You can use slicing, but better use this
# for intuition and performance.
#
print('\nstr.startswith() & str.endswith()')
print(str_one.startswith('hello'))
print(str_two.endswith('hello'))
print(str_two.endswith('hello~~'))

#
# Concatenates the string representations of
# elements in sequence seq into a string, with separator string.
# Really convenient
#
print('\nstr.join()')
print('*'.join(str_one))
print(', '.join(str_three))

#
# strlen: it is a built-in function.
#
print('\nlen()')
print(len(str_one))
print(len(str_two))

#
# lstrip, rstrip:	might be used
# 					when stripping of a newline character
#
print('\nstr.lstrip() & str.rstrip()')
print('Original: {}'.format(str_four))
print('lstrip: {}'.format(str_four.lstrip('@')))
print('rstrip: {}'.format(str_four.rstrip('@')))

#
# Replace : [old, new, max(opt)]
#
print('\nstr.replace()')
print(str_two.replace('hello', 'hi'))
print(str_two.replace('hello', 'hi', 2))

#
# split & splitlines: likely to be used when reading a file.
#
print('\nstr.split()')
print(str_two.split('hell', 1))
print(str_two.split('hell', 2))
print(str_two.split('hell', 3))