#!/usr/bin/env bash

counter=1

while [ $counter -le 10 ]; do
	echo $counter
	((counter++))
done

counter=1
until [ $counter -gt 10 ]; do
	echo $counter
	((counter++))
done

names='Stan Kyle Cartman'
for name in $names; do
	echo $name
done

for value in {1..5}; do
	echo $value
done

for value in {10..0..2}; do
	echo $value
done

