#!/usr/bin/env bash

FONTS=(
	https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/SourceCodePro.zip
	https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/Inconsolata.zip
	https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/UbuntuMono.zip
	https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/Mononoki.zip
	https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/AnonymousPro.zip
)
FONT_DIR=$HOME/.fonts

mkdir -p $FONT_DIR && {
for font in "${FONTS[@]}"; do
	wget -q "$font" -P "$FONT_DIR" && {
	font=${font##*/}
	unzip -qq -d "$FONT_DIR/${font%.zip}" "$FONT_DIR/$font"
	rm "$FONT_DIR/$font"
	}
done
} && fc-cache -fv

