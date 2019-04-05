#!/usr/bin/env bash

REMOTE_POWERLINE_CONFIG="$HOME"`
	`"/workspace/lastchicken/install/dotfiles/powerline/config.json"
LOCAL_POWERLINE_CONFIG="$HOME/.config/powerline/config.json"

PACKAGE=(
	"virtualenv"
	"powerline-status"
)

python_package () {
	for pack in ${PACKAGE[*]}; do
		pip3 install --user -q "$pack"
	done

	mkdir -p $(dirname "$LOCAL_POWERLINE_CONFIG") &&
	cp $REMOTE_POWERLINE_CONFIG $LOCAL_POWERLINE_CONFIG
}

while getopts "is" opt; do
	case "$opt" in
		"i")
			python_package
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_POWERLINE_CONFIG" "$REMOTE_POWERLINE_CONFIG"
			break;;
		*)
			break;;
	esac
done

