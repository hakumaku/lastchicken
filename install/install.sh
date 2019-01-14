#!/usr/bin/env bash

RED="\033[1;31m"
GREEN="\033[1;32m"
ORANGE="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
CYAN="\033[1;36m"
LIGHT_GRAY="\033[1;37m"
DARK_GRAY="\033[1;30m"
LIGHT_RED="\033[1;31m"
LIGHT_GREEN="\033[1;32m"
YELLOW="\033[1;33m"
LIGHT_BLUE="\033[1;34m"
LIGHT_PURPLE="\033[1;35m"
LIGHT_CYAN="\033[1;36m"
WHITE="\033[1;37m"
NC="\033[0;39m"

# Source file directory.
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
CONFIG_DIR="$DIR/config"
SRC="${BASH_SOURCE[0]}"

VIMRC_SOURCE="$CONFIG_DIR/.vimrc"
VIMRC_DEST="$HOME/.vimrc"
TMUX_SOURCE="$CONFIG_DIR/.tmux.conf"
TMUX_DEST="$HOME/.tmux.conf"
POWERLINE_SOURCE="$CONFIG_DIR/config.json"
POWERLINE_DEST="$HOME/.config/powerline/config.json"
BASHRC="$HOME/.bashrc"
TOTEM_SOURCE="$CONFIG_DIR/totem.thumbnailer"
TOTEM_DEST="/usr/share/thumbnailers"
SXIV_SOURCE="$CONFIG_DIR/image-info"
SXIV_DEST="$HOME/.config/sxiv/exec/image-info"
RANGER_SOURCE="$CONFIG_DIR/rc.conf"
RANGER_DEST="$HOME/.config/ranger/rc.conf"
ST_SOURCE="$CONFIG_DIR/config.h"
ST_DEST="$HOME/workspace/st/st*/config.h"

SOURCE_FILES=(
	$VIMRC_SOURCE
	$TMUX_SOURCE
	$POWERLINE_SOURCE
	$SXIV_SOURCE
	$RANGER_SOURCE
	$ST_SOURCE
)
DEST_FILES=(
	$VIMRC_DEST
	$TMUX_DEST
	$POWERLINE_DEST
	$SXIV_DEST
	$RANGER_DEST
	$ST_DEST
)

while getopts 's' opt; do
	case "$opt" in
		s)
			echo -e "${GREEN}Synching files...${NC}"
			for (( i=0; i<${#SOURCE_FILES[@]}; i++ )); do
				file_name=${SOURCE_FILES[$i]##*/}
				printf "\t${LIGHT_BLUE}%02d. ${CYAN}%-12s${NC}: " "$(( i + 1 ))" "${file_name}"
				# echo -e -n "\t$i. ${CYAN}${file_name}${NC}: "
				if cmp -s "${SOURCE_FILES[$i]}" "${DEST_FILES[$i]}"; then
					echo -e "No change."
				else
					echo -e "Modified."
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
	"gdebi" "valgrind"
	# blueman
	"tmux" "screenfetch" "autogen"
	"automake" "cmake" "snap"
	"fcitx-hangul" "chrome-gnome-shell" "gufw"
	"gnome-tweak-tool"
	"python3-dev" "python3-pip" "python-apt"

	# Suckless Terminal
	"libfontconfig1-dev"
	"libxft-dev"
	"libx11-dev"
	"libxext-dev"

	# Ranger
	"ranger"

	# Powerline-status fonts
	"fonts-powerline"

	# Java
	# "oracle-java11-installer"

	# For thumbnails
	"ffmpeg" "ffmpegthumbnailer"

	# OBS studio
	"obs-studio"

	# Stacer
	"stacer"

	# SMPlayer
	"smplayer" "smtube" "smplayer-themes"

	# Laptop power saving utility.
	"tlp"

	# The following two are associated with NNN. (https://github.com/jarun/nnn)
	# "libncursesw5-dev" "moreutils" "nnn"

	# Image viewer on terminal
	"sxiv"
)

PIP=(
	"virtualenv"
	"powerline-status"
)

PPA=(
	"ubuntu-make (ppa:ubuntu-desktop/ubuntu-make)"
	"Java (ppa:linuxuprising/java)"
	"Stacer (ppa:oguzhaninan/stacer)"
	"OBS studio (ppa:obsproject/obs-studio)"
	"SMPlayer (ppa:rvm/smplayer)"
	"NNN (ppa:twodopeshaggy/jarun)"
)
PPA_PATTERN="(ppa:[\/a-zA-Z-]+)"

EXTERNAL_PACKAGE=(
	"https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
	"http://media.steampowered.com/client/installer/steam.deb"
)

FAVORITE=(
	"google-chrome.desktop"
	"steam.desktop"
	"rhythmbox.desktop"
	"stacer.desktop"
)

REMOVED=()

echo_title () {
	local string=$1
	echo -e "${GREEN}$string${NC}"
}

# $1: # of columns
# $2: list
print_list () {
	local columns=$1
	local list=("${@:2}")
	local length=${#list[@]}

	for (( i=0; i<$length; i++ )); do
		printf "\t${LIGHT_BLUE}%02d. ${NC}%-18s" "$(( i + 1 ))" "${list[i]}"
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

setup_repository () {
	echo_title "The following ${#PPA[@]} PPA(s) wiil be installed:"
	print_list 1 "${PPA[@]}"
	for t in "${PPA[@]}"; do
		[[ $t =~ $PPA_PATTERN ]]
		sudo add-apt-repository -n -y ${BASH_REMATCH}
	done
	sudo apt update -qq -y
}

setup_graphics () {
	echo_title "Installing graphics drivers"
	sudo ubuntu-drivers autoinstall
}

setup_packages () {
	echo_title "The following ${#PACKAGE[@]} package(s) wiil be installed:"
	print_list 3 "${PACKAGE[@]}"
	sudo apt install -qq -y ${PACKAGE[@]}
}

setup_external_packages () {
	echo_title "The following ${#EXTERNAL_PACKAGE[@]} debian package(s) will be downloaded and installed:"
	print_list 1 "${EXTERNAL_PACKAGE[@]}"
	temp="downloaded.deb"
	for site in ${EXTERNAL_PACKAGE[*]}; do
		wget -q -O $temp $site
		sudo dpkg -i $temp
		rm $temp
	done
}

setup_vim () {
	if [[ ! -f $VIMRC_SOURCE ]]; then
		echo -e "\n${CYAN}.vimrc${NC} file does not exist in ${LIGHT_BLUE}$VIMRC_SOURCE${NC}"
		return 1
	fi
	echo_title "Setting up Vim"
	echo -e "Cloning into ${CYAN}Vundle${NC} "
	git clone -q https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

	echo -e "Copying ${CYAN}.vimrc${NC} file to ${LIGHT_BLUE}$HOME${NC} "
	sudo cp $VIMRC_SOURCE $VIMRC_DEST

	echo -e "Vundle PluginInstall "
	vim -E +PluginInstall +qall > /dev/null

	echo -e "Installing ${CYAN}YouCompleteMe${NC} "
	python3 ~/.vim/bundle/YouCompleteMe/install.py --all > /dev/null 2>&1
}

setup_communitheme () {
	echo_title "Setting up theme"
	echo -e "Downloading ${CYAN}communitheme${NC} "
	sudo snap install communitheme
}

setup_powerline () {
	if [[ ! -f $POWERLINE_SOURCE ]]; then
		echo -e "\n${CYAN}config.json${NC} file does not exist in ${LIGHT_BLUE}$POWERLINE_SOURCE${NC}"
		return 1
	fi

	echo -e "Downloading ${CYAN}powerline-status${NC} "
	for package in ${PIP[*]}; do
		pip3 install --user -q $package
	done

	echo -e "Copying ${CYAN}configure.json${NC} to ${LIGHT_BLUE}$POWERLINE_CONFIG${NC} "
	mkdir $( dirname "$POWERLINE_DEST" ) && cp $POWERLINE_SOURCE $POWERLINE_DEST
}

setup_tmux_theme () {
	if [[ ! -f $TMUX_SOURCE ]]; then
		echo -e "\n${CYAN}.tmux.conf${NC} file does not exist at ${LIGHT_BLUE}$TMUX_SOURCE${NC}"
		exit 1
	fi
	echo -e "Cloning into ${CYAN}tmux-themepack${NC}"
	git clone -q https://github.com/jimeh/tmux-themepack.git ~/.tmux-themepack

	echo -e "Copying ${CYAN}.tmux.conf${NC} to ${LIGHT_BLUE}$HOME${NC}"
	cp $TMUX_SOURCE $TMUX_DEST
}

setup_gsettings_desktop () {
	echo_title "gsettings: Desktop"
	set -x
	gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'
	gsettings set org.gnome.desktop.background show-desktop-icons 'false'
	gsettings set org.gnome.desktop.interface icon-theme 'Suru'
	gsettings set org.gnome.desktop.interface gtk-theme 'Communitheme'
	gsettings set org.gnome.desktop.interface cursor-theme 'communitheme'
	gsettings set org.gnome.desktop.interface show-battery-percentage 'true'
	gsettings set org.gnome.desktop.interface clock-show-date 'true'
	gsettings set org.gnome.desktop.interface clock-show-seconds 'true'
	gsettings set org.gnome.shell.extensions.dash-to-dock customize-alphas true
	gsettings get org.gnome.shell.extensions.dash-to-dock min-alpha
	gsettings set org.gnome.shell.extensions.dash-to-dock max-alpha 0.2
	{ set +x; } 2>/dev/null
	echo ""
}

setup_gsettings_shortcut () {
	echo_title "gsettings: Keyboard shortcuts"
	set -x
	gsettings set org.gnome.desktop.input-sources xkb-options "['korean:ralt_rctrl', 'caps:escape']"
	gsettings set org.gnome.settings-daemon.plugins.media-keys home '<Super>e'
	gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings "['/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/']"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ name "Simple Terminal"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ command "st"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ binding "<Super>Return"
	{ set +x; } 2>/dev/null
	echo ""
}

setup_gsettings_favorites () {
	echo_title "gsettings: favorites"
	for app in ${FAVORITE[*]}; do
		echo -e "'${app}'"
		gset="${gset:+"${gset}, "}'${app}'"
	done
	gsettings set org.gnome.shell favorite-apps "[${gset[*]}]"
	echo ""
}

setup_thumbnailer () {
	if [[ ! -f $TOTEM_SOURCE ]]; then
		echo -e "\n${CYAN}.totem.thumbnailer${NC} file does not exist at ${LIGHT_BLUE}$TOTEM_SOURCE${NC}"
		exit 1
	fi
	echo -e "Copying ${CYAN}totem.thumbnailer${NC} to ${LIGHT_BLUE}$TOTEM_DEST${NC}"
	sudo cp $TOTEM_SOURCE $TOTEM_DEST
}

setup_bashrc () {
	# Run this script on ".bashrc"
	printf "\n# Customized script\n" >> $BASHRC
	printf "source $CONFIG_DIR/bashrc\n\n" >> $BASHRC
}

setup_git () {
	git config --global user.email "gentlebuuny@gmail.com"
	git config --global user.name "hakumaku"
}

setup_ranger () {
	if [[ ! -f $RANGER_SOURCE ]]; then
		echo -e "\n${CYAN}rc.conf${NC} file does not exist at ${LIGHT_BLUE}$RANGER_SOURCE${NC}"
		exit 1
	fi
	echo -e "Copying ${CYAN}rc.conf${NC} to ${LIGHT_BLUE}$RANGER_DEST${NC}"
	ranger --copy-config=all
	cp $RANGER_SOURCE $RANGER_DEST
}

setup_sxiv () {
	if [[ ! -f $SXIV_SOURCE ]]; then
		echo -e "\n${CYAN}image-info${NC} file does not exist at ${LIGHT_BLUE}$SXIV_SOURCE${NC}"
		exit 1
	fi
	echo -e "Copying ${CYAN}image-info${NC} to ${LIGHT_BLUE}$SXIV_DEST${NC}"
	if [[ ! -d $HOME/.config/sxiv ]]; then
		mkdir "$HOME/.config/sxiv"
	fi
	if [[ ! -d $HOME/.config/sxiv/exec ]]; then
		mkdir "$HOME/.config/sxiv/exec"
	fi
	cp $SXIV_SOURCE $SXIV_DEST
}

function_list=(
	"add-repository"
	"grapchis driver"
	"packages"
	"external_packages"
	"vim"
	"communitheme"
	"powerline"
	"tmux-theme"
	"gsettings-desktop"
	"gsettings-shortcut"
	"gsettings-favorite"
	"thumbnailer"
	"bashrc"
	"ranger"
	"sxiv"
	"git config"
)

clear
while true; do
	echo_title "Run functions:"
	print_list 1 "${function_list[@]}"
	echo -e -n "Type number: "
	read input
	if [[ -z $input ]]; then
		echo ""
		break;
	fi

	case $input in
		1) setup_repository;;
		2) setup_graphics;;
		3) setup_packages;;
		4) setup_external_packages;;
		5) setup_vim;;
		6) setup_communitheme;;
		7) setup_powerline;;
		8) setup_tmux_theme;;
		9) setup_gsettings_desktop;;
		10) setup_gsettings_shortcut;;
		11) setup_gsettings_favorites;;
		12) setup_thumbnailer;;
		13) setup_bashrc;;
		14) setup_ranger;;
		15) setup_sxiv;;
		16) setup_git;;
		*);;
	esac
done

printf "%0.s*" {1..50}
echo -e "\nPress ${PURPLE}Super+A${NC}, search ${CYAN}language${NC}, and click to download language packs."
echo -e "Reboot and configure ${LIGHT_BLUE}Global Config${NC} of ${CYAN}fcitx-hangul${NC}."
printf "%0.s*" {1..50}
echo "\n"

