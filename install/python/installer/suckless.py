import pathlib
import urllib
import os
import requests
import tarfile
import re

# TODO:
# 1. synching config.h
# 2. git apply

class SucklessManager():
    ST_TERMINAL = 1
    DMENU = 2
    ST_URL = 'https://dl.suckless.org/st/'
    ST_REGEX = re.compile('(st-([0-9.]+).tar.gz)')
    # config.h dir
    DMENU_URL = 'https://dl.suckless.org/tools/'
    DMENU_REGEX = re.compile('(dmenu-([0-9.]+).tar.gz)')
    # config.h dir

    @staticmethod
    def run(path):
        sm.install(sm.ST_TERMINAL, path)
        sm.install(sm.DMENU, path)

    @classmethod
    def install(cls, util, path):
        """
        Untar and install util.
        """
        if util == cls.ST_TERMINAL:
            filename = cls.check_version(cls.ST_URL, cls.ST_REGEX)
            url = cls.ST_URL + filename

        elif util == cls.DMENU:
            filename = cls.check_version(cls.DMENU_URL, cls.DMENU_REGEX)
            url = cls.DMENU_URL + filename

        else:
            return

        cls.download(url, filename)
        with tarfile.open(filename) as tf:
            pathlib.Path(path).mkdir(parents=True, exist_ok=True)
            tf.extractall(path=path)
        os.remove(filename)

    @classmethod
    def check_version(cls, url, regex):
        """
        Check version for suckless programs.
        """
        contents = requests.get(url=url).content.decode('utf-8')
        versions = []

        for line in contents.splitlines():
            match = regex.search(line)

            if not match:
                continue

            versions.append((match.group(1), match.group(2)))

        versions = sorted(versions,
                key=lambda k: list(map(int, k[1].split('.'))), reverse=True)

        return versions[0][0]

    @classmethod
    def download(cls, url, filename):
        """
        Download handler.
        """
        try:
            urllib.request.urlretrieve(url, filename)

        except Exception as e:
            print(e)

if __name__ == '__main__':
    home = str(pathlib.Path.home()) + '/Downloads/st'
    SucklessManager.install(SucklessManager.ST_TERMINAL, path=home)

