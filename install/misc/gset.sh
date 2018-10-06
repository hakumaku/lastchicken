#!/usr/bin/env bash

##########################
# Create a dummy profile #
##########################
dconfdir="/org/gnome/terminal/legacy/profiles:"
new_id="$(uuidgen)"
new_name="dummy"

echo "==================="
echo "dconf and gsettings"
echo "==================="

profile_list="$(dconf read "${dconfdir}/list")"
profile_list="${profile_list:1:-1}"

for id in ${profile_list[*]}; do
	new_list+=" ${id}"
done

new_list+=${new_list:+', '}
new_list+="'${new_id}'"

dconf write "${dconfdir}/list" "[${new_list}]"
dconf write "${dconfdir}/:${new_id}/visible-name" "'${new_name}'"
dconf write "${dconfdir}/default" "'${new_id}'"

##########################
# Some terminal settings #
##########################
dconf write /org/gnome/terminal/legacy/default-show-menubar 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$new_id/ use-system-font 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$new_id/ use-theme-colors 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$new_id/ font 'Source Code Pro for Powerline Semi-Bold 12'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$new_id/ scrollbar-policy 'never'

theme_list=(
	"https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/gruvbox-dark.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/molokai.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/monokai-dark.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/one-dark.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/solarized-dark-higher-contrast.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/solarized-dark.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/solarized-light.sh"
	# "https://raw.githubusercontent.com/Mayccoll/Gogh/master/themes/wombat.sh"
)

echo "The following schemes will be installed:"
for theme in ${theme_list[*]}; do
	name=${theme##*/}
	printf "\t%s\n" ${name%.sh}
done
for theme in ${theme_list[*]}; do
	name=${theme##*/}
	wget -nv ${theme} && bash ${name} && rm ${name}
done

##############################
# Desktop interface settings #
##############################
gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'
gsettings set org.gnome.desktop.background show-desktop-icons 'false'
gsettings set org.gnome.desktop.interface icon-theme 'Suru'
gsettings set org.gnome.desktop.interface gtk-theme 'Adwaita-dark'
gsettings set org.gnome.desktop.interface cursor-theme 'communitheme'
gsettings set org.gnome.desktop.interface show-battery-percentage 'true'
gsettings set org.gnome.desktop.interface clock-show-date 'true'
gsettings set org.gnome.desktop.interface clock-show-seconds 'true'

gsettings set org.gnome.shell.extensions.dash-to-dock customize-alphas true
gsettings get org.gnome.shell.extensions.dash-to-dock min-alpha
gsettings set org.gnome.shell.extensions.dash-to-dock max-alpha 0.2

#####################
# Keyboard settings #
#####################
gsettings set org.gnome.desktop.input-sources xkb-options "['korean:ralt_rctrl', 'caps:escape']"
gsettings set org.gnome.settings-daemon.plugins.media-keys home '<Super>e'

################
# thumbnailers #
################
echo "Copying totem.thumbnailer to /usr/share/thumbnailers"
sudo cp config_file/totem.thumbnailer /usr/share/thumbnailers

