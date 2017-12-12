"""
func(value)             :   Noraml argument(matched by position)
func(name=value)        :   Keyword argument(matched by name)
func(*iterable)         :   Pass all objects in iterable as individual positional arguments.
(argument unpacking)
func(**dict)            :   Pass all key/values pairs in dict as individual keyword arguments.
(keyword argument unpacking)

def func(name)          :   Normal argument value(matches any passed value by position or name)
def func(name=value)    :   Default argument value, if not passed in the call
def func(*name)         :   Matches and collects remaining positional arguments in a tuple
def func(**name)        :   Matches and collects remaining keyword arguments in a dictionary
def func(*, name)       :   Arguments that must be passed by keyword only in calls
def func(*, name=value) :   Arguments that must be passed by keyword only in calls


closure and nested functions:
    Closure             : Inherits variables from its enclosing environment.
    Nested functions    : Otherwise...
"""

#
# def func(name)
#
def times(x, y):
    return x * y

#
# def func(name=value)
#
def times_two(x, y=2):
    return x * y

#
# def func(*args)
#
def concat(*args):
    print('args: {}'.format(type(args)))
    sep = '/'
    return sep.join(args)

#
# def func(*kwargs)
#
def table(**kwargs):
    print('kwargs: {}'.format(type(kwargs)))
    for key, value in kwargs.items():
        print('{0}: {1}'.format(key, value))

#
# def func(*, name)
#
def kwofunc(a, *, b, c):
    print(a, b, c)

#
# def func(*, name=value)
#
def kwofunc_default(a, *, b='Egg', c='Spam'):
    print(a, b, c)

#
# Closure
#
def make_printer_closure(msg):
    def printer():
        print(msg)      # Inherits msg from make_printer...
    return printer

#
# Nested Functions
#
def make_printer_nest(msg):
    def printer(msg=msg):
        print(msg)      # Note that msg of printer is DIFFERENT from
    return printer      # that of make_printer_nest.(LEGB rule)



print('times: {}'.format(times(2, 3)))
# print(times(2)) : an invalid call

print('times_two: {}'.format(times_two(2, 3)))
print('times_two: {}'.format(times_two(2)))     # y is not passed, but valid.

temp = ['Blizzard', 'Overwatch', 'HearthStone', 'Heroes of The Storm']
print(concat('Blizzard', 'Overwatch', 'HearthStone', 'Heroes of The Storm'))
print(concat(*temp))

temp = {'one': '1', 'two': '2', 'three': '3', 'four': '4'}
table(one = '1', two = '2', three = '3', four = '4')
table(**temp)

#
# kwofunc(1, 2, 3)
# TypeError: kwofunc() takes 1 positional argument but 3 were given
#
# kwofunc(1)
# TypeError: kwofunc() missing 2 required keyword-only arguments: 'b' and 'c'
#
kwofunc(1, b=2, c=3)

#
# kwofunc_default(1, 2)
# TypeError: kwofunc_default() takes 1 positional argument but 2 were given
#
kwofunc_default(1)
kwofunc_default(1, b=2)
kwofunc_default(1, b='Bacon', c='Fries')
