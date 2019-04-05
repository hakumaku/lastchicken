#!/usr/bin/env bash

PPA=(
	"ppa:tista/adapta" 					# Adapta gtk theme
	"ppa:rvm/smplayer"					# smplayer
	"ppa:nilarimogard/webupd8"			# gnome-twitch
	"ppa:umang/indicator-stickynotes"	# indicator-stickynotes
	"ppa:graphics-drivers"				# nvidia graphics drivers
	# "NNN (ppa:twodopeshaggy/jarun)"
)

PACKAGE=(
	"git" "vim" "vim-gnome"
	"g++" "curl" "ctags"
	"gdebi" "valgrind" "htop"
	"tmux" "screenfetch" "autogen"
	"automake" "cmake" "snap"
	"fcitx-hangul" "chrome-gnome-shell" "gufw"
	"gnome-tweak-tool" "gnome-shell-extensions"
	"python3-dev" "python3-pip" "python-apt"
	# blueman
	"smplayer" "smtube" "smplayer-themes" "smplayer-skins"
	"rhythmbox" "shotwell" "sxiv"
	"youtube-dl" "w3m-img" "indicator-stickynotes"

	# adapta gtk theme
	"adapta-gtk-theme"

	# Suckless Terminal & Dmenu
	# Comment the line in "config.mk" when install Dwm:
	# FREETYPEINC = ${X11INC}/freetype2
	"libx11-dev" "libxext-dev" "libxft-dev"
	"libxinerama-dev" "libfreetype6-dev"
	# "libxft2" "libfontconfig1-dev" "libpam0g-dev"
	# "libxrandr2" "libxss1"

	# For thumbnails
	"ffmpeg" "ffmpegthumbnailer"

	# Laptop power saving utility.
	# "tlp"
	# The following two are associated with NNN. (https://github.com/jarun/nnn)
	# "libncursesw5-dev" "moreutils" "nnn"

	# Twitch
	"gnome-twitch"
	"gnome-twitch-player-backend-gstreamer-cairo"
	"gnome-twitch-player-backend-gstreamer-clutter"
	"gnome-twitch-player-backend-gstreamer-opengl"
	"gnome-twitch-player-backend-mpv-opengl"
)

EXTERNAL_PACKAGE=(
	"https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
	"http://media.steampowered.com/client/installer/steam.deb"
)

# Add repository
for ppa in "${PPA[@]}"; do
	sudo add-apt-repository -n -y "$ppa"
done && {
	sudo apt update &&
	sudo apt install -qq -y "${PACKAGE[*]}"
} && {
	temp="tmp.deb"
	for site in ${EXTERNAL_PACKAGE[*]}; do
		wget -q -O $temp $site
		sudo dpkg -i $temp
		rm $temp
	done
}

