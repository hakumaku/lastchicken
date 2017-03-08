#
# What you see is what you get(WYSIWYG)
# Unlike C, the 'tab', white space, is used for
# associative statements.
#
from random import choice

x = choice([1, 2, 3])

if x == 1:
	print('Hello World!(1)')
elif x == 2:
	print('Hello World!(2)')
else:
	print('Hello World!(3)')
#
# Exception Handling
#
# try:
# 	pass
# except:
# 	pass
# except name:
# 	pass
# except name as value:
# 	pass
# except (name1, name2):
# 	pass
# except (name1, name2) as value:
# 	pass
# else:			# If no exceptions are raised in the 'try' block.
# 	pass
# finally:		# Always perform this block on exit.
# 	pass
#