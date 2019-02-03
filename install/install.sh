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
DOTFILES="$DIR/dotfiles"
SRC="${BASH_SOURCE[0]}"

VIMRC_SOURCE="$DOTFILES/.vimrc"
VIMRC_DEST="$HOME/.vimrc"
TMUX_SOURCE="$DOTFILES/.tmux.conf"
TMUX_DEST="$HOME/.tmux.conf"
POWERLINE_SOURCE="$DOTFILES/config.json"
POWERLINE_DEST="$HOME/.config/powerline/config.json"
BASHRC="$HOME/.bashrc"
TOTEM_SOURCE="$DOTFILES/totem.thumbnailer"
TOTEM_DEST="/usr/share/thumbnailers"
SXIV_SOURCE="$DOTFILES/image-info"
SXIV_DEST="$HOME/.config/sxiv/exec/image-info"
RANGER_SOURCE="$DOTFILES/rc.conf"
RANGER_DEST="$HOME/.config/ranger/rc.conf"
ST_SOURCE="$DOTFILES/st/config.h"
ST_DEST="$HOME/workspace/st/st*/config.h"
DMENU_SOURCE="$DOTFILES/dmenu/config.h"
DMENU_DEST="$HOME/workspace/dmenu/dmenu*/config.h"
DWM_SOURCE="$DOTFILES/dwm/config.h"
DWM_DEST="$HOME/workspace/dwm/dwm*/config.h"
DWM_XSESS_SOURCE="$DOTFILES/dwm/.xsessionrc"
DWM_XSESS_DEST="$HOME/.xsessionrc"

SOURCE_FILES=(
	$VIMRC_SOURCE
	$TMUX_SOURCE
	$POWERLINE_SOURCE
	$SXIV_SOURCE
	$RANGER_SOURCE
	$ST_SOURCE
	$DMENU_SOURCE
	$DWM_SOURCE
	$DWM_XSESS_SOURCE
)
DEST_FILES=(
	$VIMRC_DEST
	$TMUX_DEST
	$POWERLINE_DEST
	$SXIV_DEST
	$RANGER_DEST
	$ST_DEST
	$DMENU_DEST
	$DWM_DEST
	$DWM_XSESS_DEST
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

	# Suckless Terminal & Dmenu & DWM
	# Comment the line in "config.mk" when install Dwm:
	# FREETYPEINC = ${X11INC}/freetype2
	"libx11-dev"
	"libxext-dev"
	"libxft2"
	"libxft-dev"
	"libxinerama-dev"
	"libfreetype6-dev"
	"libfontconfig1-dev"
	"libpam0g-dev"
	"libxrandr2"
	"libxss1"

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

	# Youtube downloader
	"youtube-dl"

	# gnome-twitch
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
	"ubuntu-make (ppa:ubuntu-desktop/ubuntu-make)"
	"Java (ppa:linuxuprising/java)"
	"Stacer (ppa:oguzhaninan/stacer)"
	"OBS studio (ppa:obsproject/obs-studio)"
	"SMPlayer (ppa:rvm/smplayer)"
	"NNN (ppa:twodopeshaggy/jarun)"
	"gnome-twitch (ppa:nilarimogard/webupd8)"
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

	# Disable default bindings.
	# <Super>: overlay key
	gsettings set org.gnome.mutter overlay-key ""
	# <Super>Q: dash-to-dock
	gsettings set org.gnome.shell.extensions.dash-to-dock hot-keys false
	gsettings set org.gnome.shell.extensions.dash-to-dock shortcut-text ""
	gsettings set org.gnome.shell.extensions.dash-to-dock shortcut "[]"
	# <Super>N: focus-active-notification
	gsettings set org.gnome.shell.keybindings focus-active-notification "[]"
	# <Super>H: Hide window
	gsettings set org.gnome.shell.keybindings toggle-message-tray "[]"
	# <Super>L: Screensaver
	gsettings set org.gnome.settings-daemon.plugins.media-keys screensaver "[]"
	# <Super>P: switch-monitor
	gsettings set org.gnome.mutter.keybindings switch-monitor "['XF86Display']"
	# <Super>P: video out
	gsettings set org.gnome.settings-daemon.plugins.media-keys video-out "[]"
	# <Super>Above_Tab: switch-group
	gsettings set org.gnome.desktop.wm.keybindings switch-group "['<Alt>Above_Tab']"
	# <Super>S: toggle-overview
	gsettings set org.gnome.shell.keybindings toggle-overview "[]"

	# Window tiling keybindings
	gsettings set org.gnome.mutter.keybindings toggle-tiled-left "['<Super>H']"
	gsettings set org.gnome.mutter.keybindings toggle-tiled-right "['<Super>L']"
	gsettings set org.gnome.desktop.wm.keybindings maximize "['<Super>K']"
	gsettings set org.gnome.desktop.wm.keybindings unmaximize "['<Super>J']"
	gsettings set org.gnome.desktop.wm.keybindings minimize "['<Super>M']"

	# Switching workspaces
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-down "['<Super>N']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-up "['<Super>P']"
	# gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-left "['<Super>Left']"
	# gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-right "['<Super>Right']"

	# Move window to another workspace
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-down "['<Super><Ctrl>N']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-up "['<Super><Ctrl>P']"
	# gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-right "['<Super><Alt>Right']"
	# gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-left "['<Super><Alt>Left']"

	# Move window to another monitor
	gsettings set org.gnome.desktop.wm.keybindings move-to-monitor-left "['<Super><Ctrl>H']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-monitor-right "['<Super><Ctrl>L']"

	# Minimize window
	gsettings set org.gnome.desktop.wm.keybindings minimize "['<Super>M']"
	# Close window
	gsettings set org.gnome.desktop.wm.keybindings close "['<Super>Q', '<Alt>F4']"
	# Disable animation
	gsettings set org.gnome.desktop.interface enable-animations false
	# Text ellipsis limit
	gsettings set org.gnome.nautilus.desktop text-ellipsis-limit 1
	gsettings set org.gnome.nautilus.icon-view text-ellipsis-limit "['1']"

	# Hide ubuntu dash-to-dock
	gsettings set org.gnome.shell.extensions.dash-to-dock autohide false
	gsettings set org.gnome.shell.extensions.dash-to-dock dock-fixed false
	gsettings set org.gnome.shell.extensions.dash-to-dock intellihide false

	# Switching to specific workspace
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-1 "['<Super>1']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-2 "['<Super>2']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-3 "['<Super>3']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-4 "['<Super>4']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-5 "['<Super>5']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-6 "['<Super>6']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-7 "['<Super>7']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-8 "['<Super>8']"
	gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-9 "['<Super>9']"

	# Move window to specific workspace
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-1 "['<Super><Ctrl>1']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-2 "['<Super><Ctrl>2']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-3 "['<Super><Ctrl>3']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-4 "['<Super><Ctrl>4']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-5 "['<Super><Ctrl>5']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-6 "['<Super><Ctrl>6']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-7 "['<Super><Ctrl>7']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-8 "['<Super><Ctrl>8']"
	gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-9 "['<Super><Ctrl>9']"

	# Sound control
	# Unlike 'wm', media-keys does not support
	# list of multiple keys, but string only.
	# Thus, the audio keys, such as 'XF86AudioRaiseVolume',
	# which some keyboards have will be disabled.
	# I have tried to bind these keys to custom-keybindings to run 'amixer',
	# but it did not go well. The commands were:
	# 'amixer set Master 3%+'
	# 'amixer -q sset Master 3%+'
	# 'amixer -q -D pulse sset Master 10%+'
	# 'amixer -M get Master'
	# 'pactl set-sink-volume 0 +15%'
	gsettings set org.gnome.settings-daemon.plugins.media-keys volume-up "<Super>equal"
	gsettings set org.gnome.settings-daemon.plugins.media-keys volume-down "<Super>minus"
	gsettings set org.gnome.settings-daemon.plugins.media-keys volume-mute "<Super>0"

	# Customized shortcuts
	gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings "[\
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom2/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom3/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/' ]"

	# custom0: Shutdown
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ name "Shutdown"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ command "gnome-session-quit --power-off"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ binding "<Super>Above_Tab"

	# custom1: gnome-tweaks
	# ubuntu 18.04 has bug that it cannot bind "<Super>O".
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/ name "Gnome Tweaks"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/ command "gnome-tweaks"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/ binding "<Super>U"

	# custom2: Calculator
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom2/ name "Calculator"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom2/ command "gnome-calculator"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom2/ binding "<Super>C"

	# custom3: Simple Terminal
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom3/ name "Simple Terminal"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom3/ command "st"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom3/ binding "<Super>Return"

	# custom4: Dmenu
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/ name "Dmenu"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/ command "dmenu_run"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/ binding "<Super>S"

	# custom5: Web browser
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/ name "Web browser"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/ command "google-chrome"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/ binding "<Super>W"

	# custom6: Twitch TV
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/ name "Twitch"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/ command "gnome-twitch"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/ binding "<Super>T"

	# custom7: Steam
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/ name "Steam"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/ command "steam"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/ binding "<Super>G"

	# custom8: nvidia
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/ name "Nvidia dmenu"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/ command "$DIR/nvidia.sh"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/ binding "<Super>semicolon"

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
	printf "source $DOTFILES/bashrc\n\n" >> $BASHRC
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

place_st_icon () {
	sudo cp "$DOTFILES/st/st.png" "/usr/share/icons/hicolor/256x256/apps/"
}

place_dwm_icon () {
	sudo cp "$DOTFILES/dwm/dwm.desktop" "/usr/share/xsessions/"
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
	"place st icon"
	"place dwm icon"
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
		17) place_st_icon;;
		18) place_dwm_icon;;
		*);;
	esac
done

printf "%0.s*" {1..50}
echo -e "\nPress ${PURPLE}Super+A${NC}, search ${CYAN}language${NC}, and click to download language packs."
echo -e "Reboot and configure ${LIGHT_BLUE}Global Config${NC} of ${CYAN}fcitx-hangul${NC}."
printf "%0.s*" {1..50}
echo "\n"

