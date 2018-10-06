#!/usr/bin/env bash

pip_list=(
	"virtualenv"
	"powerline-status"
)

powerline_setting="# powerline-status
if [ -d "\$HOME/.local/bin" ]; then
	PATH="\$HOME/.local/bin:\$PATH"
fi
export POWERLINE_COMMAND=powerline
if [ -f ~/.local/lib/python3*/site-packages/powerline/bindings/bash/powerline.sh ]; then
	source ~/.local/lib/python3*/site-packages/powerline/bindings/bash/powerline.sh
fi
"

tmux_setting="# tmux
[ -z "$TMUX" ] && command -v tmux >/dev/null && TERM=xterm-256color exec tmux
"

bash_settings="# bash settings
set -o vi
export EDITOR=/usr/bin/vim
bind -m vi-insert \"\C-l\":clear-screen
alias=ls='ls --color -h --group-directories-first'
screenfetch
"

bash_line=(
	"$powerline_setting"
	# "$tmux_setting"
)

###############################
# Communitheme and Suru icons #
###############################
echo "Installing communitheme"
theme="communitheme"
sudo snap install $theme

################
# pip packages #
################
echo "Downloading python packages"
for package in ${pip_list[*]}; do
	pip3 install --user -q $package
done

##############################################################
# powerline-status configuration (~/.bashrc and config.json) #
##############################################################
echo "Setting ~/.bashrc"
for line in "${bash_line[@]}"; do
	echo "$line" >> ~/.bashrc
done

powerline_config_dir="$HOME/.config/powerline"
echo "Copying configure.json to $powerline_config_dir"
mkdir $powerline_config_dir && cp config_file/config.json $powerline_config_dir

# powerline-font (https://github.com/powerline/fonts)
echo "Downloading powerline-font"
git clone https://github.com/powerline/fonts.git --depth=1
cd fonts && ./install.sh && cd .. && rm -rf fonts

############################################################
# tmux-themepack (https://github.com/jimeh/tmux-themepack) #
############################################################
echo "Downloading tmux-themepack"
git clone https://github.com/jimeh/tmux-themepack.git ~/.tmux-themepack
echo "Copying tmux.conf to $HOME"
cp config_file/.tmux.conf ~/.tmux.conf

