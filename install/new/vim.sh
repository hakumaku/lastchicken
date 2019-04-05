#!/usr/bin/env bash

REMOTE_VIMRC="$HOME/workspace/lastchicken/install/dotfiles/vim/.vimrc"
LOCAL_VIMRC="$HOME/.vimrc"

vim () {
	# $1: local .vimrc
	# $2: remote .vimrc
	local local_vimrc="$1"
	local remote_vimrc="$2"
	if [ ! -f "$remote_vimrc" ]; then
		echo ".vimrc does not exist: $remote_vimrc"
		return
	fi

	git clone -q https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim &&
	cp $remote_vimrc $local_vimrc &&
	{ vim -E +PluginInstall +qall > /dev/null; } &&
	{ python3 ~/.vim/bundle/YouCompleteMe/install.py --all > /dev/null 2>&1; }
}

while getopts "is" opt; do
	case "$opt" in
		"i")
			vim $LOCAL_VIMRC $REMOTE_VIMRC
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_VIMRC" "$REMOTE_VIMRC"
			break;;
		*)
			break;;
	esac
done

