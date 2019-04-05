#!/usr/bin/env bash

LOCAL_TMUX_CONF="$HOME/.tmux.conf"
REMOTE_TMUX_CONF="$HOME/workspace/lastchicken/install/dotfiles/tmux/.tmux.conf"

tmux () {
	if [ ! -f "$REMOTE_TMUX_CONF" ]; then
		echo ".tmux.conf file does not exist: $REMOTE_TMUX_CONF"
		return
	fi
	git clone -q https://github.com/jimeh/tmux-themepack.git ~/.tmux-themepack
	cp "$REMOTE_TMUX_CONF" "$LOCAL_TMUX_CONF"
}

while getopts "is" opt; do
	case "$opt" in
		"i")
			tmux
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_TMUX_CONF" "$REMOTE_TMUX_CONF"
			break;;
		*)
			break;;
	esac
done

