#!/usr/bin/env bash

echo "Downloading Vundle"
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
echo "Copying vimrc to $HOME"
sudo cp config_file/.vimrc ~/.vimrc
vim +PluginInstall +qall
echo "Installing YouCompleteMe(Vim plugin)"
python3 ~/.vim/bundle/YouCompleteMe/install.py --all

