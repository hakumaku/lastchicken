#!/usr/bin/env bash

conf="/etc/NetworkManager/conf.d/default-wifi-powersave-on.conf"
sed '/wifi.powersave/s/[0-9]/2/' $conf

