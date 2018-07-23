#!/usr/bin/env bash

string_var="Command"

# double-bracket syntax
# It is not portable.
# It is used, when comparing strings.
if [[ "$string_var" == *[cC]ommand* ]]; then
	echo "Command has been typed."
fi

