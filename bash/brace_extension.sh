#!/usr/bin/env bash

echo {1..5}.js

name="John"

echo ${name}
echo ${name/J/j}
echo ${name:0:2}
echo ${name::2}
echo ${name::-1}
val="default"
# $val, if not $food.
echo ${food:-$val}
# $food to $val.
echo ${food:=$val}
# $val, if $food.
echo ${food:+$val}

length=2
echo ${name:0:length}

path="/path/to/foo.cpp"
echo ${path%.cpp}
echo ${path%.cpp}.o

# Remove prefix
echo ${path#*/}
# basepath
# Remove long prefix
echo ${path##*/}
# Extension
echo ${path##*.}

path="/path/path/path/to/foo.cpp"
# Replace one
echo ${path/path/bar}
# Replace all
echo ${path//path/bar}

# Dirpath
base=${path##*/}
dir=${path%$base}
echo $dir

