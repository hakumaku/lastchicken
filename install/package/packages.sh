#!/usr/bin/env bash

ppa_list=(
	"ubuntu-make (ppa:ubuntu-desktop/ubuntu-make)"
	"Java (ppa:linuxuprising/java)"
	"NVIDIA graphics (ppa:graphics-drivers/ppa)"
	"Stacer (ppa:oguzhaninan/stacer)"
	"OBS studio (ppa:obsproject/obs-studio)"
	"SMPlayer (ppa:rvm/smplayer)"
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
	# "blueman"
	"tmux"
	"autogen"
	"automake"
	"cmake"
	"snap"
	"fcitx-hangul"
	"chrome-gnome-shell"
	"gufw"
	"gnome-tweak-tool"
	"python3-dev"
	"python3-pip"
	"python-apt"	# Steam requires
	"ffmpeg"
	"ffmpegthumbnailer"
	"obs-studio"
	"screenfetch"
	"smplayer"			# SMPlayer
	"smtube"			# SMPlayer
	"smplayer-themes"	# SMPlayer	
	"tlp"			# for power saving.
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
sudo apt upgrade -qq -y

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
sudo apt autoremove -y
sudo apt autoclean -y

echo "Configure manually gufw and fcitx-hangul"
echo "Everything is finished!"

