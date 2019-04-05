#!/usr/bin/env bash

# Script for miscellaneous configurations

LOCAL_TOTEM="/usr/share/thumbnailers/totem.thumbnailer"
REMOTE_TOTEM="$HOME"`
	`"/workspace/lastchicken/install/dotfiles/gif/totem.thumbnailer"

LOCAL_SMPLAYER="$HOME/.config/smplayer/smplayer.ini"
REMOTE_SMPLAYER="$HOME"`
	`"/workspace/lastchicken/install/dotfiles/smplayer/smplayer.ini"

# bashrc

smplayer () {
	[ -f $REMOTE_SMPLAYER ] && mkdir -p $HOME/.config/smplayer &&
	cp "$REMOTE_SMPLAYER" "$LOCAL_SMPLAYER"
}

thumbnailer () {
	[ -f $TOTEM_SOURCE ] && sudo cp "$REMOTE_TOTEM" "$LOCAL_TOTEM"
}

twitch_icon () {
	local icon="$HOME/workspace/lastchicken/install/dotfiles/twitch_icons/twitch128px.png"
	icon="${icon//\//\\\/}"
	sudo sed -i 's/\(Icon=\)com.vinszent.GnomeTwitch/1\'"${icon}"'/' /usr/share/applications/com.vinszent.GnomeTwitch.desktop
}

git_config () {
	git config --global user.email "gentlebuuny@gmail.com"
	git config --global user.name "hakumaku"
}

while getopts "is" opt; do
	case "$opt" in
		"i")
			smplayer
			thumbnailer
			twitch_icon
			git_config
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_TOTEM" "$REMOTE_TOTEM"
			sync_dotfile "$LOCAL_SMPLAYER" "$REMOTE_SMPLAYER"
			break;;
		*)
			break;;
	esac
done

