#!/usr/bin/env bash

foo=3
# Spaces are necessary.
# [$foo -ge 3] is invalid syntax.
if [ $foo -ge 3 ]; then
	echo "foo is greater than 3"
fi

# test is a built-in function.
if test $foo -ge 3; then
	echo "foo is greater than 3"
fi

if [ $foo -gt 6 ]; then
	echo "foo is greater than 6."
elif [ $foo -gt 3 ]; then
	echo "foo is greater than 3 and less than 6."
else
	echo "foo is less than 3."
fi

if [ -f array.sh ]; then
	echo "array.sh exists."
fi

if [ -r array.sh ]; then
	echo "array.sh is readable."
fi

