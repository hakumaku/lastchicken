#!/usr/bin/env bash

LOCAL_RC_CONF="$HOME/.config/ranger/rc.conf"
REMOTE_RC_CONF="$HOME/workspace/lastchicken/install/dotfiles/ranger/rc.conf"
DIR="$HOME/workspace"

ranger () {
	# $1: local rc.conf
	# $2: remote rc.conf
	# $3: install directory
	local local_rc_conf="$1"
	local remote_rc_conf="$2"
	local dir="$3"
	if [ ! -f "$remote_rc_conf" ]; then
		echo "rc.conf does not exist: $remote_rc_conf"
		return
	fi

	git clone -q https://github.com/ranger/ranger "$dir" &&
	mkdir -p "~/.config/ranger" && cp "$remote_rc_conf" "$local_rc_conf" &&
	(cd "$dir/ranger" && python3 ranger.py --copy-config=all && sudo make install) &&
	# Uncomment video preview script
	sed -i '/# Video$/{
		n
		s/# //
		n
		s/# //
		n
		s/# //
		n
		s/# //
	}' "$HOME/.config/ranger/scope.sh"
}

ranger_devicons () {
	# $1: install directory
	local dir="$1"
	git clone -q https://github.com/alexanderjeurissen/ranger_devicons "$dir" &&
	(cd "$dir/ranger_devicons" && make install)
}

while getopts "i:s" opt; do
	case "$opt" in
		"i")
			if [ "$OPTARG" == "ranger" ]; then
				ranger "$LOCAL_RC_CONF" "$REMOTE_RC_CONF" "$DIR"
			elif [ "$OPTARG" == "ranger_devicons" ]; then
				ranger_devicons "$DIR"
			fi
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_RC_CONF" "$REMOTE_RC_CONF"
			break;;
		*)
			break;;
	esac
done

