#!/usr/bin/env bash

dir="$(dirname "$0")"
while getopts "is" opt; do
	case "$opt" in
		"i")
			break;;
		"s")
			source "$dir"/foo.sh
			bash ./config.sh -s
			# source "$dir""/powerline.sh" -s
			# source "$dir""/ranger.sh" -s
			# source "$dir""/suckless.sh" -s
			# source "$dir""/sxiv.sh" -s
			# source "$dir""/tmux.sh" -s
			# source "$dir""/vim.sh" -s
			break;;
		*)
			break;;
	esac
done

