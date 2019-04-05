import subprocess

class GsetManager():
    FAVORITES = (
        'google-chrome.desktop',
        'steam.desktop',
        'com.vinszent.GnomeTwitch.desktop',
        'rhythmbox.desktop',
        'smplayer.desktop',
        'shotwell.desktop',
        'st.desktop',
        'org.gnome.Nautilus.desktop',
        'org.gnome.tweaks.desktop',
        'gnome-control-center.desktop',
        'nvidia-settings.desktop',
    )

    CMDS = (
        'gsettings set org.gnome.desktop.background show-desktop-icons false',
        'gsettings set org.gnome.desktop.background picture-options scaled',
        'gsettings set org.gnome.desktop.screensaver picture-options scaled',
        'gsettings set org.gnome.desktop.interface show-battery-percentage true',
        'gsettings set org.gnome.desktop.interface clock-show-date true',
        'gsettings set org.gnome.desktop.interface clock-show-seconds true',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock apply-custom-theme false',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock custom-theme-shrink true',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock click-action minimize',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock customize-alphas true',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock dock-position BOTTOM',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock transparency-mode FIXED',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock background-opacity 0.3',
        # 'gsettings set org.gnome.shell.extensions.dash-to-dock max-alpha 0.2',

        'gsettings set org.gnome.desktop.interface gtk-theme Adapta-Eta',
        'gsettings set org.gnome.desktop.interface icon-theme Suru++',
        'gsettings set org.gnome.desktop.interface cursor-theme DMZ-Black',
        'gsettings set org.gnome.shell.extensions.user-theme name Adapta-Eta',
    )

    @staticmethod
    def run():
        # shell = subprocess.Popen('/bin/bash', stdin=subprocess.PIPE)
        with subprocess.Popen('/bin/bash', stdin=subprocess.PIPE) as shell:
            shell.stdin.write('set -x\n'.encode('utf-8'))
            for cmd in GsetManager.CMDS:
                byte_cmd = str.encode(cmd + '\n')
                shell.stdin.write(byte_cmd)
            byte_cmd = str.encode(GsetManager.gset_favorites() + '\n')
            shell.stdin.write(byte_cmd)
        # GsetManager.gset_favorites(shell)
        # shell.wait()

    @classmethod
    def gset_favorites(cls):
        fav = ['\\"{}\\"'.format(app) for app in cls.FAVORITES]
        return "gsettings set org.gnome.shell favorite-apps \"[{}]\"".format(
                ', '.join(fav))

if __name__ == '__main__':
    GsetManager.run()

