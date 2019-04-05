#!/usr/bin/env bash

sync_dotfile () {
	# $1: local file
	# $2: remote file
	local new="$1"
	local old="$2"
	local filename="$(basename "$(dirname "$new")")"/"$(basename -- "$new")"

	if cmp -s "$new" "$old"; then
		echo $filename
	else
		echo "$filename*"
		cp "$new" "$old"
	fi
}

