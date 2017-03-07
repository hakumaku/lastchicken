#
# What you see is what you get(WYSIWYG)
# Unlike C, the 'tab', white space, is used for
# associative statements.
# Way better use for-loop over while-loop
# if the implementation is not so non-intuitive.
#
from random import choice

x = choice([1, 2, 3])

if x == 1:
	print('Hello World!(1)')
elif x == 2:
	print('Hello World!(2)')
else:
	print('Hello World!(3)')

for x in range(1,3):
	print(x)