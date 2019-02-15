DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

FAVORITE=(
	"google-chrome.desktop"
	"steam.desktop"
	"com.vinszent.GnomeTwitch.desktop"
	"rhythmbox.desktop"
	"smplayer.desktop"
	"shotwell.desktop"
	"st.desktop"
	"org.gnome.Nautilus.desktop"
	"org.gnome.tweaks.desktop"
	"gnome-control-center.desktop"
	"nvidia-settings.desktop"
)

function_list=(
	"Desktop Environment"
	"Shortcuts"
	"Favorites"
	"Theme"
)

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

gsettings_desktop () {
	echo "gsettings: Desktop"
	set -x
	gsettings set org.gnome.desktop.background show-desktop-icons 'false'
	gsettings set org.gnome.desktop.interface show-battery-percentage 'true'
	gsettings set org.gnome.desktop.interface clock-show-date 'true'
	gsettings set org.gnome.desktop.interface clock-show-seconds 'true'

	gsettings set org.gnome.shell.extensions.dash-to-dock apply-custom-theme 'false'
	gsettings set org.gnome.shell.extensions.dash-to-dock custom-theme-shrink 'true'
	gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'
	gsettings set org.gnome.shell.extensions.dash-to-dock customize-alphas true
	gsettings set org.gnome.shell.extensions.dash-to-dock dock-position 'BOTTOM'
	gsettings set org.gnome.shell.extensions.dash-to-dock transparency-mode 'FIXED'
	gsettings set org.gnome.shell.extensions.dash-to-dock background-opacity 0.3
	# gsettings get org.gnome.shell.extensions.dash-to-dock min-alpha
	gsettings set org.gnome.shell.extensions.dash-to-dock max-alpha 0.2
	{ set +x; } 2>/dev/null
	echo ""
}

gsettings_shortcut () {
	echo "gsettings: Keyboard shortcuts"
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
	gsettings set org.gnome.desktop.interface enable-animations true
	# Text ellipsis limit
	gsettings set org.gnome.nautilus.desktop text-ellipsis-limit 1
	gsettings set org.gnome.nautilus.icon-view text-ellipsis-limit "['1']"

	# Set all false to hide ubuntu dash-to-dock
	gsettings set org.gnome.shell.extensions.dash-to-dock autohide false
	gsettings set org.gnome.shell.extensions.dash-to-dock dock-fixed false
	gsettings set org.gnome.shell.extensions.dash-to-dock intellihide true
	# dash-to-dock theme
	gsettings set org.gnome.shell.extensions.dash-to-dock apply-custom-theme true

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
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom9/', \
		'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom10/' ]"

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

	# custom4: Ranger
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/ name "Ranger"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/ command "st -e 'ranger'"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/ binding "<Super>R"

	# custom5: Dmenu
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/ name "Dmenu"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/ command "dmenu_run"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/ binding "<Super>S"

	# custom6: Web browser
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/ name "Web browser"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/ command "google-chrome"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/ binding "<Super>W"

	# custom7: Music Player
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/ name "Music Player"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/ command "rhythmbox"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/ binding "<Super>Y"

	# custom8: Twitch TV
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/ name "Twitch"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/ command "gnome-twitch"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/ binding "<Super>T"

	# custom9: Steam
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom9/ name "Steam"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom9/ command "steam"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom9/ binding "<Super>G"

	# custom10: nvidia
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom10/ name "Nvidia dmenu"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom10/ command "$DIR/nvidia.sh"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom10/ binding "<Super>semicolon"

	{ set +x; } 2>/dev/null
	echo ""
}

gsettings_favorites () {
	echo "gsettings: favorites"
	for app in ${FAVORITE[*]}; do
		echo -e "'${app}'"
		gset="${gset:+"${gset}, "}'${app}'"
	done
	gsettings set org.gnome.shell favorite-apps "[${gset[*]}]"
	echo ""
}

apply_theme() {
	echo "gsettings: theme"
	set -x

	gsettings set org.gnome.desktop.interface gtk-theme "Adapta-Eta"
	gsettings set org.gnome.desktop.interface icon-theme "Suru++"
	gsettings set org.gnome.desktop.interface cursor-theme "DMZ-Black"
	gsettings set org.gnome.shell.extensions.user-theme name "Adapta-Eta"

	{ set +x; } 2>/dev/null
	echo ""
}

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
		1) gsettings_desktop;;
		2) gsettings_shortcut;;
		3) gsettings_favorites;;
		4) apply_theme;;
		*);;
	esac
done

