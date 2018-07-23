#!/usr/bin/env bash

# Array
arr=("Hello" "World")
echo $arr

arr[0]="Foo"
arr[1]="Bar"
echo ${arr[0]} ${arr[1]}

# All of the items in the array
echo ${arr[*]}
# All of the indexes in the array
echo ${!arr[*]}
# Number of items in the array
echo ${#arr[*]}
# Length of item zero
echo ${#arr[0]}

array=("one" "two" "three" "four" [5]="five")
echo "Array size: ${#array[*]}"
echo "Array items:"
for item in ${array[*]}; do
	printf "\t%s\n" $item
done

echo "Array indexes:"
for index in ${!array[*]}; do
	printf "\t%d\n" $index
done

echo "Array items and indexes:"
for index in ${!array[*]}; do
	printf "%4d: %s\n" $index ${array[$index]}
done

array=("First item" "Second item" "Third" "item")

echo "Number of items in original array: ${#array[*]}"
for ix in ${!array[*]}; do
	printf "\t%s\n" "${array[$ix]}"
done
echo

# Unquoted expansion
# Separated by space
arr=(${array[*]})
echo "After unquoted expansion: ${#arr[*]}"
for ix in ${!arr[*]}; do
	printf "\t%s\n" "${arr[$ix]}"
done
echo

# * expansion
# All items are combined.
arr=("${array[*]}")
echo "After * expansion: ${#arr[*]}"
for ix in ${!arr[*]}; do
	printf "\t%s\n" "${arr[$ix]}"
done
echo

# @ expansion
# Expected result.
arr=("${array[@]}")
echo "After @ expansion: ${#arr[*]}"
for ix in ${!arr[*]}; do
	printf "\t%s\n" "${arr[$ix]}"
done

