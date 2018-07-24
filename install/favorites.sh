favorites=(
	"google-chrome.desktop"
	"steam.desktop"
	"rhythmbox.desktop"
	"stacer.desktop"
)

for app in ${favorites[*]}; do
	echo "'${app}'"
	gset="${gset:+"${gset}, "}'${app}'"
done

gsettings set org.gnome.shell favorite-apps "[${gset[*]}]"

