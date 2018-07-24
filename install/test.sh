echo "gnome-tweak-tool settings"
# profile_id="$(dconf list /org/gnome/terminal/legacy/profiles:/)"
profile_id="$(gsettings get org.gnome.Terminal.ProfilesList default)"
profile_id="${profile_id:1:-1}"
echo "======"
echo $profile_id
echo "======"
dconf write /org/gnome/terminal/legacy/default-show-menubar 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$profile_id/ use-system-font 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$profile_id/ use-theme-colors 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$profile_id/ font 'Source Code Pro for Powerline Semi-Bold 12'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/:$profile_id/ scrollbar-policy 'never'

gsettings set org.gnome.shell.extensions.dash-to-dock click-action 'minimize'
gsettings set org.gnome.desktop.background show-desktop-icons 'false'
gsettings set org.gnome.desktop.interface icon-theme 'Suru'
gsettings set org.gnome.desktop.interface gtk-theme 'Adwaita-dark'
gsettings set org.gnome.desktop.interface cursor-theme 'communitheme'
gsettings set org.gnome.desktop.input-sources xkb-options "['korean:ralt_rctrl', 'caps:escape']"
gsettings set org.gnome.desktop.interface show-battery-percentage 'true'
gsettings set org.gnome.desktop.interface clock-show-date 'true'
gsettings set org.gnome.desktop.interface clock-show-seconds 'true'

gsettings set org.gnome.settings-daemon.plugins.media-keys home '<Super>e'

