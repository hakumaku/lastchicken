#!/usr/bin/env bash

im-config -n fcitx
options=(
	LC_NUMERIC=en_US.UTF-8
	LC_TIME=en_US.UTF-8
	LC_MONETARY=en_US.UTF-8
)
sudo update-locale "${options[@]}"

