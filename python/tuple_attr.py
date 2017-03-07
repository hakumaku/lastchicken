# Tuple is immutable.

tuple1 = ('physics', 'chemistry', 1, 2, 3)
tuple2 = ('a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'a', 'a', 'a')
tuple3 = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

#
# Slicing
#
print(tuple1)
print(tuple1[0])
print(tuple2[:4])
print(tuple2[2:])
print(tuple1 + tuple2)

#
# Invalid Syntax
# 	tuple1[5] = 4
# 	tuple2[1] = 'z'
# Instead, you gotta create a new tuple.
#
tuple4 = tuple1 + tuple([4])
print('\n{}'.format(tuple4))

print('\nmax() & min()')
print(max(tuple3))
print(min(tuple3))

#
# tuple.count() & tuple.index()
#
print('{0} {1} {2} {3}'.format(tuple2.count('a'), tuple2.count('b'),
							tuple2.index('a'), tuple2.index('b')))