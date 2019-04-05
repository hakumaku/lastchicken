#!/usr/bin/env bash

dir="$(dirname "$0")"
while getopts "is" opt; do
	case "$opt" in
		"i")
			echo "Apt"
			bash "$dir""/apt.sh"
			echo "Nerd-font"
			bash "$dir""/font.sh"
			echo "Suckless Terminal"
			bash "$dir""/suckless.sh" -i st
			echo "Dmenu"
			bash "$dir""/suckless.sh" -i dmenu
			echo "Powerline"
			bash "$dir""/powerline.sh" -i
			echo "Ranger"
			bash "$dir""/ranger.sh" -i ranger
			echo "Ranger_devicons"
			bash "$dir""/ranger.sh" -i ranger_devicons
			echo "Sxiv"
			bash "$dir""/sxiv.sh" -i

			echo "Vim"
			bash "$dir""/vim.sh" -i
			echo "Tmux"
			bash "$dir""/tmux.sh" -i

			echo "Adapta"
			bash "$dir""/adapta.sh"
			echo "Suru"
			bash "$dir""/suru.sh"
			echo "gnome-shell-extension"
			python3 "$dir""/gnome.py"
			echo "Gnome desktop environment configuration"
			bash "$dir""/config.sh" -i
			bash "$dir""/gsettings.sh"
			bash "$dir""/korean.sh"
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

