#!/usr/bin/env python3

import subprocess
import urllib
import os
import requests
import re

def lsd():
    URL = 'https://github.com/Peltoche/lsd/releases'
    deb_regex = re.compile('(lsd_([0-9.]+)_amd64.deb)')
    contents = requests.get(url=URL).content.decode('utf-8').splitlines()
    version_list = []

    for line in contents:
        if 'download' not in line:
            continue

        match = deb_regex.search(line)

        if not match:
            continue

        version_list.append((match.group(1), match.group(2)))

    version_list = sorted(version_list,
            key=lambda k: list(map(int, k[1].split('.'))), reverse=True)
    filename, version = version_list[0]

    download_url = 'https://github.com/Peltoche/lsd/releases/download/{}/{}'\
            .format(version, filename)

    urllib.request.urlretrieve(download_url, filename)
    subprocess.run(['sudo', 'dpkg', '-i', filename])
    os.remove(filename)

if __name__ == '__main__':
    lsd()

