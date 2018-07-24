#!/usr/bin/env bash

site_list=(
	"https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
	"http://media.steampowered.com/client/installer/steam.deb"
)

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


