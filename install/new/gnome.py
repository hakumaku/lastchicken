import subprocess
import pathlib
import urllib
import zipfile
import os
import json
import requests
import re

class GnomeInstaller():
    GNOME_URL = 'https://extensions.gnome.org'
    INSTALL_DIR = str(pathlib.Path.home()) + '/.local/share/gnome-shell/extensions/'
    VERSION = re.search('[a-zA-Z\s]*([\d.]+)*',
        subprocess.run(['gnome-shell', '--version'],
            stdout=subprocess.PIPE).stdout.decode('utf-8')
        ).group(1)

    @staticmethod
    def run(pk):
        """
        Call this function to install gnome shell extensions.
        """
        info = GnomeInstaller.query(pk)

        if not info:
            print('Could not retrieve meta data of pk({}).'.format(pk))
            return

        GnomeInstaller.install(*info)

    @classmethod
    def query(cls, pk):
        """
        Retrieve metadata of the extension with pk.
        """
        # name = name.replace(' ', '%20')
        # query = GNOME_URL + '/extension-query/?search=' + str(name)
        query = cls.GNOME_URL + '/extension-info/?pk={}'.format(pk)
        ext = requests.get(url=query).json()

        uuid = ext.get('uuid')
        shell_version = ext.get('shell_version_map')
        version = list(shell_version)

        if not version:
            print('Recevied empty version', ext.get('name'))
            return

        v = cls.match_version(version)
        if not v:
            print('Unexpected error has occured while auto-matching version.')
            return

        return (uuid, shell_version[v]['version'])

    @classmethod
    def install(cls, uuid, version, filename='temp.zip'):
        """
        Download extension with uuid and version.
        """
        url = cls.GNOME_URL + \
            '/extension-data/{}.v{}.shell-extension.zip'.format(uuid, version)
        dirname = cls.INSTALL_DIR + uuid

        try:
            urllib.request.urlretrieve(url, filename)

        except urllib.error.HTTPError:
            print('Url: '.format(url))
            print('uuid: '.format(uuid))
            print('version: '.format(version))
            print(urllib.error.HTTPError.code)

        except urllib.error.URLError:
            print('Url: '.format(url))
            print('uuid: '.format(uuid))
            print('version: '.format(version))
            print(urllib.error.URLError.reason)

        pathlib.Path(dirname).mkdir(parents=True, exist_ok=True)
        with zipfile.ZipFile(filename, 'r') as zf:
            zf.extractall(dirname)
        subprocess.run(['gnome-shell-extension-tool', '-e', uuid])
        os.remove(filename)

    @classmethod
    def match_version(cls, version_list):
        """
        Always select the version less than or equal to the current.
        """
        versions = sorted(version_list + [ cls.VERSION ], reverse=True)
        for i, v in enumerate(versions):
            if v == cls.VERSION:
                return versions[i+1]

        return

# Gnome Shell Extension
EXTENSION_ID = (
    (1036, 'Extensions'),
    (19, 'User Themes'),
    (805, 'Hide Dash X'),
    (744, 'Hide Activites Button'),
    (1267, 'No Title Bar'),
    (307, 'Dash to Dock'),
    (15, 'AlternateTab'),
    (750, 'OpenWeather'),
    (1080, 'Transparent Notification'),
    (517, 'Caffeine'),
    (1683, 'Draw on You screen'),
)

if __name__ == '__main__':
    for ext in EXTENSION_ID:
        print('Extension name: '.format(ext[1]), end='')
        GnomeInstaller.run(ext[0])

