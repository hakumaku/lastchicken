#!/usr/bin/env bash

dir="$(dirname "$0")/script"
while getopts "isb" opt; do
	case "$opt" in
		"i")
			echo "Apt" && bash "$dir""/apt.sh"
			echo "Nerd-font" && bash "$dir""/font.sh"
			echo "Suckless Terminal" && bash "$dir""/suckless.sh" -i st
			echo "Dmenu" && bash "$dir""/suckless.sh" -i dmenu
			echo "Powerline" && bash "$dir""/powerline.sh" -i
			echo "Ranger" && bash "$dir""/ranger.sh" -i ranger
			echo "Ranger_devicons" && bash "$dir""/ranger.sh" -i ranger_devicons
			echo "Sxiv" && bash "$dir""/sxiv.sh" -i
			echo "Youtube-dl" && bash "$dir""/youtube-dl.sh"

			echo "Vim" && bash "$dir""/vim.sh" -i
			echo "Tmux" && bash "$dir""/tmux.sh" -i
			echo "Adapta" && bash "$dir""/adapta.sh"
			echo "Suru" && bash "$dir""/suru.sh"
			echo "gnome-shell-extension" && python3 "$dir""/gnome.py"
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
		"b")
			printf "source $HOME/workspace/lastchicken/install/dotfiles/bashrc" >>\
				"$HOME/.bashrc"
			break;;
		*)
			break;;
	esac
done

