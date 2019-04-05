#!/usr/bin/env bash

suru_plus () {
	{ wget -qO- https://raw.githubusercontent.com/gusbemacbe/suru-plus/master/install.sh | sh; } &&
	{ wget -qO- https://git.io/fhQdI | sh; } &&
	suru-plus-folders -C cyan --theme Suru++
}

