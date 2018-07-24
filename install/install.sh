#!/usr/bin/env bash

site_list=(
	"https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
)

package_list=(
	"stacer"
	"vim"
	"g++"
	"git"
	"curl"
	"ctags"
	"gdebi"
	"valgrind"
	"blueman"
	"tmux"
	"autogen"
	"automake"
	"snap"
	"fcitx-hangul"
	"chrome-gnome-shell"
	"gufw"
	"gnome-tweak-tool"
	"python3-dev"
	"python3-pip"
	"ffmpeg"
	"ffmpegthumbnailer"
)

ppa_list=(
	"ubuntu-make (ppa:ubuntu-desktop/ubuntu-make)"
	"Java (ppa:linuxuprising/java)"
	"NVIDIA graphics (ppa:graphics-drivers/ppa)"
	"Stacer (ppa:oguzhaninan/stacer)"
)

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

pip_list=(
	"virtualenv"
	"powerline-status"
)

powerline_setting="# powerline-status
if [ -d "$HOME/.local/bin" ]; then
	PATH="$HOME/.local/bin:$PATH"
fi
export POWERLINE_COMMAND=powerline
if [ -f ~/.local/lib/python3*/site-packages/powerline/bindings/bash/powerline.sh ]; then
	source ~/.local/lib/python3*/site-packages/powerline/bindings/bash/powerline.sh
fi
"

tmux_setting="# tmux
if command -v tmux>/dev/null; then
	[[ ! $TERM =~ screen ]] && [ -z $TMUX ] && exec tmux
fi
"

bash_line=(
	"$powerline_setting"
	"$tmux_setting"
)

pattern="(ppa:[\/a-zA-Z-]+)"

echo "The following ppa will be added:"
for ppa in "${ppa_list[@]}"; do
	printf "\t%s\n" "${ppa}"
done
for ppa in "${ppa_list[@]}"; do
	[[ $ppa =~ $pattern ]]
	echo $ppa
	sudo add-apt-repository -n -y ${BASH_REMATCH[1]}
done
sudo apt update -qq

echo "The following packages will be installed:"
for package in ${package_list[*]}; do
	printf "\t%s\n" $package
done
sudo apt install -qq -y ${package_list[*]}

echo "The following packages will be downloaded, then installed:"
for site in ${site_list[*]}; do
	printf "\t%s\n" $site
done
for site in ${site_list[*]}; do
	d=downloaded.deb
	wget -nv -O $d $site
	sudo dpkg -i $d
	rm $d
done

echo "The following schemes will be installed:"
for theme in ${theme_list[*]}; do
	name=${theme##*/}
	printf "\t%s\n" ${name%.sh}
done
for theme in ${theme_list[*]}; do
	name=${theme##*/}
	wget -nv ${theme} && bash ${name} && rm ${name}
done

echo "Installing communitheme"
theme="communitheme"
sudo snap install $theme

echo "Setting ~/.bashrc"
for line in "${bash_line[@]}"; do
	echo "$line" >> ~/.bashrc
done

# tmux-themepack (https://github.com/jimeh/tmux-themepack)
echo "Downloading tmux-themepack"
git clone https://github.com/jimeh/tmux-themepack.git ~/.tmux-themepack
echo "Copying tmux.conf to $HOME"
cp tmux.conf ~/.tmux.conf

echo "Downloading python packages"
for package in ${pip_list[*]}; do
	pip3 install --user -q $package
done

# powerline-status configure.json
powerline_config_dir="$HOME/.config/powerline"
echo "Copying configure.json to $powerline_config_dir"
mkdir $powerline_config_dir && cp configure.json $powerline_config_dir

# powerline-font (https://github.com/powerline/fonts)
echo "Downloading powerline-font"
git clone https://github.com/powerline/fonts.git --depth=1
cd fonts && ./install.sh && cd .. && rm -rf fonts

# gnome-tweak-tool settings
echo "gnome-tweak-tool settings"
profile_id="$(dconf list /org/gnome/terminal/legacy/profiles:/)"
echo $profile_id
dconf write /org/gnome/terminal/legacy/default-show-menubar 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/$profile_id use-system-font 'false'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/$profile_id font 'Source Code Pro for Powerline Semi-Bold 12'
gsettings set org.gnome.Terminal.Legacy.Profile:/org/gnome/terminal/legacy/profiles:/$profile_id scrollbar-policy 'never'

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

echo "Copying totem.thumbnailer to /usr/share/thumbnailers"
sudo cp totem.thumbnailer /usr/share/thumbnailers

echo "Downloading Vundle"
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
echo "Copying vimrc to $HOME"
sudo cp vimrc ~/.vimrc
vim +PluginInstall +qall
echo "Installing YouCompleteMe(Vim plugin)"
python3 ~/.vim/bundle/YouCompleteMe/install.py --all

echo "Installing Java"
sudo apt install -qq -y oracle-java10-installer
sudo apt install -qq -y oracle-java10-set-default
# umake android

echo "Installing Node.js"
curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
sudo apt install -qq -y nodejs

echo "Installing graphics driver."
echo "Reboot is required after installation."
sudo ubuntu-drivers autoinstall
# sudo apt install nvidia-cuda-toolkit gcc-6
sudo apt autoremove
sudo apt autoclean

echo "Configure manually gufw and fcitx-hangul"
echo "Everything is finished!"

