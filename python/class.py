#
# Some class interface technique keywords(pg896):
#	1) Super
#	2) Inheritor
#	3) Replacer
#	4) Extender
#	5) Provider
#
#*******************************************************************
#
# obj.__init__()	Constructor
# obj.__del__()		Destructor
# obj.__repr__()	the official representation as a string
# obj.__str__()		the informal value as a string
# obj.__bytes__()	the informal value as a byte array
# obj.__format__()	the value as a formatted string
# 
# obj.__iter__()
# obj.__next__()
# obj.__reversed__()
#
# obj.__getattribute__()		to fetch attribute (unconditionally)
# obj.__getattr__()				to fetch attribute (fallback)
#	*An example is given below.*
#
# obj.__setattr__()				to set an attribute
# obj.__delattr__()				to delete an attribute
# obj.__dir__()					to list all attributes and methods
# obj.__call__()				to act like a function
# obj.__len__()					the number of items
# obj.__contains__()			It is for the 'in' membership operator.
#
# obj.__getitem__()				x[key]
# obj.__setitem__()				x[key] = value
# obj.__delitem__()				del x[key]
# obj.__missing__()				x[nonexistent_key]
#
#*******************************************************************
#
# obj.__add__()			obj.__radd__()
# obj.__sub__()			obj.__rsub__()
# obj.__mul__()			obj.__rmul__()
# obj.__truediv__()		obj.__rtruediv__()
# obj.__floordiv__()	obj.__rfloordiv__()
# obj.__mod__()			obj.__rmod__()
# obj.__pow__()			obj.__rpow__()
# obj.__lshift__()		obj.__rlshift__()
# obj.__rshift__()		obj.__rrshift__()
# obj.__and__()			obj.__rand__()
# obj.__xor__()			obj.__rxor__()
# obj.__or__()			obj.__ror__()
#
# obj.__neg__()			obj.__pos__()
# obj.__abs__()			obj.__invert__()
# obj.__complex__()		obj.__int__()
# obj.__float__()		obj.__round__()
# obj.__ceil__()		obj.__floor__()
# obj.__trunc__()
#
# obj.__eq__()			obj.__ne__()
# obj.__lt__()			obj.__le__()
# obj.__gt__()			obj.__ge__()
# obj.__bool__()
#

#
# __getattr__ vs __getattribute__
#
if __name__ == '__main__':
	class Dynamo:
		def __getattr__(self, key):
			if key == 'color':			# The attribute name is passed into here, FALLBACK.
				return 'PapayaWhip'
			else:						# When accessing wrong attributes.
				raise AttributeError

	dyn = Dynamo()						# The class, Dynamo, does not have '.color',
	print(dyn.color)					# it calls __getattr__() to make an attribute, '.color'.
	dyn.color = 'LemonChiffon'			# Since it now has '.color', it does not call __getattr__().
	print(dyn.color)					# Properly shows 'LemonChiffon'

	class SuperDynamo:
		def __getattribute__(self, key):
			if key == 'color':			# The attribute name is passed into here, UNCONDITIONALLY.
				return 'PapayaWhip'
			else:						# When accessing wrong attributes.
				raise AttributeError

	dyn = SuperDynamo()					# The class, SuperDynamo, does not have '.color',
	print(dyn.color)					# it calls __getattribute__() to make an attribute, '.color'.
	dyn.color = 'LemonChiffon'			# Unlike __getattr__(), __getattribute__() is *still called*
	print(dyn.color)					# to provide a value for dyn.color.
										# You probably want to define a __setattr__() method at once
										# and coordinatebetween them to keep track of attribute values.
	#
	# Pitfall
	#
	class Rastan:
		def __getattribute__(self, key):
			raise AttributeError
		def swim(self):
			pass
	# hero = Rastan()
	# hero.swim()						# This is never gonna be made.