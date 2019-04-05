import subprocess
import os

class PackageManager():
    PPA=(
            'ppa:tista/adapta', # Adapta GTK theme
            'ppa:rvm/smplayer', # SMPlayer
            'ppa:nilarimogard/webupd8', # gnome-twitch
            'ppa:umang/indicator-stickynotes', # indicator-stickynotes
            # 'NNN (ppa:twodopeshaggy/jarun)'
    )

    PACKAGE=(
            'git', 'vim', 'vim-gnome',
            'g++', 'curl', 'ctags',
            'gdebi', 'valgrind', 'htop',
            'tmux','screenfetch','autogen'
            'automake','cmake','snap'
            'fcitx-hangul','chrome-gnome-shell','gufw'
            'gnome-tweak-tool','gnome-shell-extensions'
            'python3-dev','python3-pip','python-apt'
            # blueman
            'smplayer','smtube','smplayer-themes'
            'rhythmbox','shotwell','sxiv'
            'youtube-dl','w3m-img','indicator-stickynotes'

            # adapta gtk theme
            'adapta-gtk-theme'

            # Suckless Terminal & Dmenu
            # Comment the line in 'config.mk' when install Dwm:
            # FREETYPEINC = ${X11INC}/freetype2
            'libx11-dev','libxext-dev','libxft-dev'
            'libxinerama-dev','libfreetype6-dev'
            # 'libxft2','libfontconfig1-dev','libpam0g-dev'
            # 'libxrandr2','libxss1'

            # For thumbnails
            'ffmpeg','ffmpegthumbnailer'

            # Laptop power saving utility.
            # 'tlp'
            # The following two are associated with NNN. (https://github.com/jarun/nnn)
            # 'libncursesw5-dev','moreutils','nnn'

            # Twitch
            'gnome-twitch',
            'gnome-twitch-player-backend-gstreamer-cairo',
            'gnome-twitch-player-backend-gstreamer-clutter',
            'gnome-twitch-player-backend-gstreamer-opengl',
            'gnome-twitch-player-backend-mpv-opengl',
    )

    PIP=(
            'virtualenv',
            'powerline-status',
    )

    URL=(
        "https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb"
        "http://media.steampowered.com/client/installer/steam.deb"
    )

    @staticmethod
    def run():
        with subprocess.Popen(
                '/bin/bash', stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE) as shell:
            AptManager.add_repository(shell)
            AptManager.apt_install(shell)
            AptManager.pip_install(shell)
            shell.stdin.close()
            for line in shell.stdout.readlines():
                print(line)

    @classmethod
    def add_repository(cls, shell):
        cmd = 'echo sudo add-apt-repository -n -y'
        for ppa in cls.PPA:
            full_cmd = '{} {}\n'.format(cmd, ppa).encode('utf-8')
            shell.stdin.write(full_cmd)
        shell.stdin.write('echo sudo apt update -qq -y\n'.encode('utf-8'))

    @classmethod
    def gnome_package(cls, shell):
        cmd = 'echo sudo apt install {}\n'.format(
                ' '.join(cls.PACKAGE)).encode('utf-8')
        shell.stdin.write(cmd)

    @classmethod
    def python_package(cls, shell):
        cmd = 'echo pip3 install --user -q'
        for package in cls.PIP:
            full_cmd = '{} {}\n'.format(cmd, package).encode('utf-8')
            shell.stdin.write(full_cmd)

    @classmethod
    def debian_package(cls, shell):
        for url in cls.URL:
            pass

if __name__ == '__main__':
    AptManager.run()

