#!/usr/bin/env bash

LOCAL_IMAGE_SXIV="$HOME/.config/sxiv/exec/image-info"
REMOTE_IMAGE_SXIV="$HOME/workspace/lastchicken/install/dotfiles/sxiv/image-info"
LOCAL_RIFLE_SXIV="/usr/local/bin/sxiv-rifle"
REMOTE_RIFLE_SXIV="$HOME/workspace/lastchicken/install/dotfiles/sxiv/sxiv-rifle"

sxiv () {
	if [ ! -f "$REMOTE_IMAGE_SXIV" ] || [ ! -f "$REMOTE_RIFLE_SXIV" ]; then
		echo "Missing remote files:"
		echo "\t$REMOTE_IMAGE_SXIV"
		echo "\t$REMOTE_RIFLE_SXIV"
		return
	fi

	local mime="$HOME/.config/mimeapps.list"

	mkdir -p "$HOME/.config/sxiv/exec" &&
	cp "$REMOTE_IMAGE_SXIV" "$LOCAL_IMAGE_SXIV" &&
	sudo cp "$REMOTE_RIFLE_SXIV" "$LOCAL_RIFLE_SXIV" &&
	sudo sed -i 's/Exec=sxiv/&-rifle/' /usr/share/applications/sxiv.desktop && {
	if [ -f $mime ]; then
		sudo sed -i '/\[Default Applications\]/a\
		image/gif=sxiv.desktop\
		image/bmp=sxiv.desktop\
		image/gif=sxiv.desktop\
		image/jpeg=sxiv.desktop\
		image/jpg=sxiv.desktop\
		image/png=sxiv.desktop\
		image/tiff=sxiv.desktop\
		image/x-bmp=sxiv.desktop\
		image/x-portable-anymap=sxiv.desktop\
		image/x-portable-bitmap=sxiv.desktop\
		image/x-portable-graymap=sxiv.desktop\
		image/x-tga=sxiv.desktop\
		image/x-xpixmap=sxiv.desktop
		' $HOME/.config/mimeapps.list
	else
		touch $mime
		local string=$(cat <<- END
		[Default Applications]
		image/gif=sxiv.desktop
		image/bmp=sxiv.desktop
		image/gif=sxiv.desktop
		image/jpeg=sxiv.desktop
		image/jpg=sxiv.desktop
		image/png=sxiv.desktop
		image/tiff=sxiv.desktop
		image/x-bmp=sxiv.desktop
		image/x-portable-anymap=sxiv.desktop
		image/x-portable-bitmap=sxiv.desktop
		image/x-portable-graymap=sxiv.desktop
		image/x-tga=sxiv.desktop
		image/x-xpixmap=sxiv.desktop

		END
		)
		printf "$string" >> $mime
	fi }
}

while getopts "is" opt; do
	case "$opt" in
		"i")
			sxiv
			break;;
		"s")
			# import sync_dotfile ()
			source "$(dirname "$0")""/sync.sh"
			sync_dotfile "$LOCAL_IMAGE_SXIV" "$REMOTE_IMAGE_SXIV"
			sync_dotfile "$LOCAL_RIFLE_SXIV" "$REMOTE_RIFLE_SXIV"
			break;;
		*)
			break;;
	esac
done

