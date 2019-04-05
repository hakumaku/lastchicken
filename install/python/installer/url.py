import urllib
import requests
import json

class UrlParser():
    def __init__(self, *args, **kwargs):
        pass
    # versions = sorted(versions,
    #         key=lambda k: list(map(int, k[1].split('.'))), reverse=True)

    @classmethod
    def check_version(cls, url, regex):
        """
        Retrieve matching string in the given url.
        """
        contents = requests.get(url=url).content.decode('utf-8')
        string = []

        for line in contents.splitlines():
            if not line:
                continue

            match = regex.search(line)

            if not match:
                continue

            string.append(match.group())

        return string

    @classmethod
    def download(cls, url, filename):
        try:
            urllib.request.urlretrieve(url, filename)

        except HTTPError:
            print(HTTPError.code)

        except URLError:
            print(URLError.reason)

