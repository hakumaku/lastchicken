#!/usr/bin/env bash

# $(...)
# Execute the command in the parens
# in a subshell and return its stdout.
echo "The current date is $(date)"
echo

# (...)
# Run the commands listed in the parens in a subshell.
a=1
(a=2; echo "inside: a=$a")	# 2 is assigned to 'a' in a subshell.
echo "outside a=$a"			# 'a' is still 1.
echo

# $((...))
# Perform arithmetic and return the result of the calculation.
a=$((2 + 3))
echo "a=$a"
echo

# ${...}
# Return the value of the shell variable named in the braces.
echo ${SHELL}
echo

# {...}
# Execute the commands in the braces as a group.
false || { echo "We failed"; exit 1; }

