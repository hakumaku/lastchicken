#!/usr/bin/env bash

dir="$(dirname "$0")"
while getopts "is" opt; do
	case "$opt" in
		"i")
			bash "$dir""/apt.sh"
			bash "$dir""/font.sh"
			bash "$dir""/suckless.sh" -i st
			bash "$dir""/suckless.sh" -i dmenu
			bash "$dir""/powerline.sh" -i
			bash "$dir""/ranger.sh" -i ranger
			bash "$dir""/ranger.sh" -i ranger_devicons
			bash "$dir""/sxiv.sh" -i

			bash "$dir""/vim.sh" -i
			bash "$dir""/tmux.sh" -i

			bash "$dir""/adapta.sh"
			bash "$dir""/suru.sh"
			python3 "$dir""/gnome.py"
			bash "$dir""/config.sh" -i
			bash "$dir""/gsettings.sh"
			break;;
		"s")
			bash "$dir""/config.sh" -s
			bash "$dir""/powerline.sh" -s
			bash "$dir""/ranger.sh" -s
			bash "$dir""/suckless.sh" -s
			bash "$dir""/sxiv.sh" -s
			bash "$dir""/tmux.sh" -s
			bash "$dir""/vim.sh" -s
			break;;
		*)
			break;;
	esac
done

