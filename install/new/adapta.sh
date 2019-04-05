#!/usr/bin/env bash

DIR="$HOME/workspace"
OPTIONS="--enable-parallel --disable-cinnamon --disable-flashback"`
	`"--disable-xfce --disable-mate --disable-openbox"`
	`"--enable-gtk_next --with-selection_color --with-accent_color"`
	`"--with-suggestion_color --with-destruction_color"

sudo rm -rf /usr/share/themes/{Adapta,Adapta-Eta,Adapta-Nokto,Adapta-Nokto-Eta}
rm -rf ~/.local/share/themes/{Adapta,Adapta-Eta,Adapta-Nokto,Adapta-Nokto-Eta}
rm -rf ~/.themes/{Adapta,Adapta-Eta,Adapta-Nokto,Adapta-Nokto-Eta}

sudo apt install autoconf automake inkscape libgdk-pixbuf2.0-dev \
	libglib2.0-dev libxml2-utils pkg-config sassc parallel &&
git clone -q https://github.com/adapta-project/adapta-gtk-theme "$DIR" &&
(cd "$DIR/adapta-gtk-theme" && ./autogen.sh --prefix=/usr "$OPTIONS" &&
	make && sudo make install)

