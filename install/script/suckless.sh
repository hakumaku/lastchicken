#!/usr/bin/env bash

LOCAL_ST_CONFIG="$HOME/workspace/st/config.h"
REMOTE_ST_CONFIG="$HOME/workspace/lastchicken/install/dotfiles/st/config.h"
ST_DESKTOP="$HOME/workspace/lastchicken/install/dotfiles/st/st.desktop"

LOCAL_DMENU_CONFIG="$HOME/workspace/dmenu/config.h"
REMOTE_DMENU_CONFIG="$HOME/workspace/lastchicken/install/dotfiles/dmenu/config.h"

install () {
	# $1: install directory
	# $2: remote config.h
	# $3: url
	# $4: package
	local dir="$1"
	local config="$2"
	local url="$3"
	local package="$4"

	mkdir -p "$dir" &&
	wget -q "$url$package" -P "$dir" &&
	tar xf "$dir/$package" -C "$dir" --strip-components=1 &&
	cp $config $dir &&
	(cd "$dir" && make && sudo make install && make clean)
}

suckless_terminal () {
	# $1: local config.h
	# $2: remote config.h
	local dir="${1/config.h}"
	local config="$2"
	if [ ! -f "$config" ]; then
		echo "config.h does not exist: $config"
		return
	fi

	local url="https://dl.suckless.org/st/"
	local package="$(wget -q "$url" -O - | grep -o "st-\([0-9].\)*tar.gz" | sort -V | tail -1)"
	if [ -z "$package" ]; then
		echo "Cannot parse the link."
		return
	fi

	install "$dir" "$config" "$url" "$package" &&
	cp "$ST_DESKTOP" "$HOME/.local/share/applications"
}

dmenu () {
	# $1: local config.h
	# $2: remote config.h
	local dir="${1/config.h}"
	local config="$2"
	if [ ! -f "$config" ]; then
		echo "config.h does not exist: $config"
		return
	fi

	local url="https://dl.suckless.org/tools/"
	local package="$(wget -q "$url" -O - | grep -o "dmenu-\([0-9].\)*tar.gz" | sort -V | tail -1)"
	if [ -z "$package" ]; then
		echo "Cannot parse the link."
		return
	fi

	install "$dir" "$config" "$url" "$package"
}

while getopts "i:s" opt; do
	case "$opt" in
		"i")
			if [ "$OPTARG" == "st" ]; then
				suckless_terminal "$LOCAL_ST_CONFIG" "$REMOTE_ST_CONFIG"
			elif [ "$OPTARG" == "dmenu" ]; then
				dmenu "$LOCAL_DMENU_CONFIG" "$REMOTE_DMENU_CONFIG"
			fi
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_ST_CONFIG" "$REMOTE_ST_CONFIG"
			sync_dotfile "$LOCAL_DMENU_CONFIG" "$REMOTE_DMENU_CONFIG"
			break;;
		*)
			break;;
	esac
done

