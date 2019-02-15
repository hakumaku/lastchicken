#!/usr/bin/env bash

# Source file directory.
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
DOTFILES="$DIR/dotfiles"
SRC="${BASH_SOURCE[0]}"

VIMRC_SOURCE="$DOTFILES/vim/.vimrc"
VIMRC_DEST="$HOME/.vimrc"
TMUX_SOURCE="$DOTFILES/tmux/.tmux.conf"
TMUX_DEST="$HOME/.tmux.conf"
POWERLINE_SOURCE="$DOTFILES/powerline/config.json"
POWERLINE_DEST="$HOME/.config/powerline/config.json"
BASHRC="$HOME/.bashrc"
TOTEM_SOURCE="$DOTFILES/gif/totem.thumbnailer"
TOTEM_DEST="/usr/share/thumbnailers"
SXIV_SOURCE="$DOTFILES/sxiv/image-info"
SXIV_DEST="$HOME/.config/sxiv/exec/image-info"
RANGER_SOURCE="$DOTFILES/ranger/rc.conf"
RANGER_DEST="$HOME/.config/ranger/rc.conf"

ST_SOURCE="$DOTFILES/st/config.h"
ST_DEST="$HOME/workspace/st/config.h"
DMENU_SOURCE="$DOTFILES/dmenu/config.h"
DMENU_DEST="$HOME/workspace/dmenu/config.h"

SMPLAYER_SOURCE="$DOTFILES/smplayer/smplayer.ini"
SMPLAYER_DEST="$HOME/.config/smplayer/smplayer.ini"

SOURCE_FILES=(
	$VIMRC_SOURCE
	$TMUX_SOURCE
	$POWERLINE_SOURCE
	$SXIV_SOURCE
	$RANGER_SOURCE
	$ST_SOURCE
	$DMENU_SOURCE
	$SMPLAYER_SOURCE
)
DEST_FILES=(
	$VIMRC_DEST
	$TMUX_DEST
	$POWERLINE_DEST
	$SXIV_DEST
	$RANGER_DEST
	$ST_DEST
	$DMENU_DEST
	$SMPLAYER_DEST
)

while getopts 's' opt; do
	case "$opt" in
		s)
			echo "Synching files..."
			for (( i=0; i<${#SOURCE_FILES[@]}; i++ )); do
				file_name=${SOURCE_FILES[$i]##*/}
				printf "\t%02d. %-12s: " "$(( i + 1 ))" "${file_name}"
				# echo -n "\t$i. ${CYAN}${file_name}${NC}: "
				if cmp -s "${SOURCE_FILES[$i]}" "${DEST_FILES[$i]}"; then
					echo "No change."
				else
					echo "Modified."
					cp ${DEST_FILES[$i]} ${SOURCE_FILES[$i]}
				fi
			done
			exit 0
		;;
	esac
done

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
	"smplayer" "smtube" "smplayer-themes"
	"rhythmbox" "shotwell" "sxiv"
	"youtube-dl"

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

PIP=(
	"virtualenv"
	"powerline-status"
)

PPA=(
	"Adapta-GTK-Theme (ppa:tista/adapta)"
	"SMPlayer (ppa:rvm/smplayer)"
	"gnome-twitch (ppa:nilarimogard/webupd8)"
	# "NNN (ppa:twodopeshaggy/jarun)"
)
PPA_PATTERN="(ppa:[\/0-9a-zA-Z-]+)"

EXTERNAL_PACKAGE=(
	"https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
	"http://media.steampowered.com/client/installer/steam.deb"
)

REMOVED=()

# $1: # of columns
# $2: list
print_list () {
	local columns=$1
	local list=("${@:2}")
	local length=${#list[@]}

	for (( i=0; i<$length; i++ )); do
		printf "\t%02d. %-18s" "$(( i + 1 ))" "${list[i]}"
		if [[ $(( $(( i + 1 )) % $columns )) -eq 0 ]]; then
			echo ""
		fi
	done
	echo ""
}

read_file () {
	local -n string=$1
	local stream=$2

	while IFS='' read -r line; do
		if [[ ${line[0]:0:1} == '#' ]] || [[ -z $line ]]; then
			continue
		fi
		string+=("$line")
	done < "$stream"
}

add_apt_repository () {
	echo "The following ${#PPA[@]} PPA(s) wiil be installed:"
	print_list 1 "${PPA[@]}"
	for t in "${PPA[@]}"; do
		[[ $t =~ $PPA_PATTERN ]]
		sudo add-apt-repository -n -y ${BASH_REMATCH}
	done
	sudo apt update -qq -y
}

nvidia_driver () {
	echo "Installing graphics drivers"
	sudo add-apt-repository -n -y "ppa:graphics-drivers"
	sudo apt update
	sudo ubuntu-drivers devices
	sudo ubuntu-drivers autoinstall
}

apt_install () {
	echo "The following ${#PACKAGE[@]} package(s) wiil be installed:"
	print_list 3 "${PACKAGE[@]}"
	sudo apt install -qq -y ${PACKAGE[@]}
}

external_program () {
	echo "The following ${#EXTERNAL_PACKAGE[@]} debian package(s) will be downloaded and installed:"
	print_list 1 "${EXTERNAL_PACKAGE[@]}"
	temp="downloaded.deb"
	for site in ${EXTERNAL_PACKAGE[*]}; do
		wget -q -O $temp $site
		sudo dpkg -i $temp
		rm $temp
	done
}

suckless () {
	cd $HOME/workspace
	local st="https://dl.suckless.org/st/"
	local st_dir="${ST_DEST/config.h/}"
	local dmenu="https://dl.suckless.org/tools/"
	local dmenu_dir="${DMENU_DEST/config.h/}"
	local latest=""

	latest=$( wget -q $st -O - | grep -o "st-\([0-9].\)*tar.gz" | tail -1)
	echo "Downloading" "$latest"
	wget -q "$st$latest"
	mkdir "$st_dir" && tar xf "$latest" -C "$st_dir" --strip-components 1
	echo "Installing $latest"
	cp $ST_SOURCE $ST_DEST
	cp "$DOTFILES/st/st.desktop" "$HOME/.local/share/applications/"
	cd "$st_dir" && make && sudo make install && make clean && cd ..

	latest=$( wget -q $dmenu -O - | grep -o "dmenu-\([0-9].\)*tar.gz" | tail -1)
	echo "Downloading" "$latest"
	wget -q "$dmenu$latest"
	mkdir "$dmenu_dir" && tar xf "$latest" -C "$dmenu_dir" --strip-components 1
	echo "Installing $latest"
	cp $DMENU_SOURCE $DMENU_DEST
	cd "$dmenu_dir" && make && sudo make install && make clean && cd ..

	cd $DIR
}

vim () {
	if [[ ! -f $VIMRC_SOURCE ]]; then
		echo "\n.vimrc file does not exist in $VIMRC_SOURCE"
		return 1
	fi
	echo "Setting up Vim"
	echo "Cloning into Vundle"
	git clone -q https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

	echo "Copying .vimrc file to $HOME"
	cp $VIMRC_SOURCE $VIMRC_DEST

	echo "Vundle PluginInstall "
	vim -E +PluginInstall +qall > /dev/null

	echo "Installing YouCompleteMe"
	python3 ~/.vim/bundle/YouCompleteMe/install.py --all > /dev/null 2>&1
}

powerline () {
	if [[ ! -f $POWERLINE_SOURCE ]]; then
		echo "\nconfig.json file does not exist in $POWERLINE_SOURCE"
		return 1
	fi

	echo "Downloading powerline-status"
	for package in ${PIP[*]}; do
		pip3 install --user -q $package
	done

	echo "Copying configure.json to $POWERLINE_CONFIG"
	mkdir $( dirname "$POWERLINE_DEST" ) && cp $POWERLINE_SOURCE $POWERLINE_DEST

	git clone -q https://github.com/powerline/fonts.git --depth=1
	cd fonts && ./install.sh && cd .. && rm -rf fonts
}

tmux_theme () {
	if [[ ! -f $TMUX_SOURCE ]]; then
		echo "\n.tmux.conf file does not exist at $TMUX_SOURCE"
		exit 1
	fi
	echo "Cloning into tmux-themepack"
	git clone -q https://github.com/jimeh/tmux-themepack.git ~/.tmux-themepack

	echo "Copying .tmux.conf to $HOME"
	cp $TMUX_SOURCE $TMUX_DEST
}

bashrc () {
	# Run this script on ".bashrc"
	printf "\n# Customized script\n" >> $BASHRC
	printf "source $DOTFILES/bashrc\n\n" >> $BASHRC
}

ranger () {
	if [[ ! -f $RANGER_SOURCE ]]; then
		echo "\nrc.conf file does not exist at $RANGER_SOURCE"
		exit 1
	fi
	cd $HOME/workspace

	echo "Downloading ranger"
	git clone -q https://github.com/ranger/ranger
	echo "Copying rc.conf to $RANGER_DEST"
	mkdir ~/.config/ranger
	cp $RANGER_SOURCE $RANGER_DEST
	cd ranger && python3 ranger.py --copy-config=all && sudo make install && cd ..

	echo "Downloading ranger_devicons"
	git clone -q https://github.com/alexanderjeurissen/ranger_devicons
	cd ranger_devicons && make install && cd ..

	echo "Downloading Nerd Font"
	mkdir NerdFont && cd NerdFont && wget -q https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/UbuntuMono.zip
	find -name '*.zip' -exec sh -c 'unzip -d "${1%.*}" "$1" && cp -a "${1%.*}" ~/.fonts' _ {} \; && fc-cache -fv

	cd $DIR
}

sxiv () {
	if [[ ! -f $SXIV_SOURCE ]]; then
		echo "\nimage-info file does not exist at $SXIV_SOURCE"
		exit 1
	fi
	echo "Copying image-info to $SXIV_DEST"
	if [[ ! -d $HOME/.config/sxiv ]]; then
		mkdir "$HOME/.config/sxiv"
	fi
	if [[ ! -d $HOME/.config/sxiv/exec ]]; then
		mkdir "$HOME/.config/sxiv/exec"
	fi
	cp $SXIV_SOURCE $SXIV_DEST
}

smplayer() {
	mkdir $HOME/.config/smplayer && cp $SMPLAYER_SOURCE $SMPLAYER_DEST
}

git_config () {
	git config --global user.email "gentlebuuny@gmail.com"
	git config --global user.name "hakumaku"
}

thumbnailer () {
	if [[ ! -f $TOTEM_SOURCE ]]; then
		echo "\n.totem.thumbnailer file does not exist at $TOTEM_SOURCE"
		exit 1
	fi
	echo "Copying totem.thumbnailer to $TOTEM_DEST"
	sudo cp $TOTEM_SOURCE $TOTEM_DEST
}

suru_plus_icon() {
	wget -qO- https://raw.githubusercontent.com/gusbemacbe/suru-plus/master/install.sh | sh
	wget -qO- https://git.io/fhQdI | sh
	suru-plus-folders -C cyan --theme Suru++
}

twitch_icon () {
	local dest="Icon=$DOTFILES/twitch_icons/twitch128px.png"
	dest="${dest//\//\\\/}"
	sudo sed -i -e 's/Icon=com.vinszent.GnomeTwitch/'"${dest}"'/g' /usr/share/applications/com.vinszent.GnomeTwitch.desktop
}

function_list=(
	"Add Repository"
	"Grapchis Driver"
	"Packages"
	"External Packages"
	"Suckless Utilities"
	"Vim"
	"Powerline"
	"Tmux Theme"
	"Ranger"
	"Bashrc"
	"Sxiv"
	"Smplayer"
	"Thumbnailer"
	"Git Config"
	"Suru++"
	"Replace Twitch Icon"
)

clear
while true; do
	echo "Run functions:"
	print_list 1 "${function_list[@]}"
	echo -n "Type number: "
	read input
	if [[ -z $input ]]; then
		echo ""
		break;
	fi

	case $input in
		1) add_apt_repository;;
		2) nvidia_driver;;
		3) apt_install;;
		4) external_program;;
		5) suckless;;
		6) vim;;
		7) powerline;;
		8) tmux_theme;;
		9) ranger;;
		10) bashrc;;
		11) sxiv;;
		12) smplayer;;
		13) thumbnailer;;
		14) git_config;;
		15) suru_plus_icon;;
		16) twitch_icon;;
		*);;
	esac
done

printf "%0.s*" {1..50}
echo "\nPress Super+A, search language, and click to download language packs."
echo "Reboot and configure Global Config of fcitx-hangul."
printf "%0.s*" {1..50}
echo "\n"

