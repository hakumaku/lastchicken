x = set('abcde')
y = set('cdefghi')
z = set('abcdefghijkl')

print(x)
print(y)

width = 20
print('Difference'.ljust(width) + ': ' + str(x - y))
print('Union : '.ljust(width) + ': ' + str(x | y))
print('Intersection'.ljust(width) + ': ' + str(x & y))
print('Symmetric difference'.ljust(width) + ': ' + str(x ^ y))
print('Superset'.ljust(width) + ': ' + str(z > y))
print('Subset'.ljust(width) + ': ' + str(x < z))