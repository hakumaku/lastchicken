#!/usr/bin/env bash
choices="Auto\n""Adaptive\n""Performance\n"
chosen=$(echo -e "$choices" | dmenu -p "Nivida Powermizer")

list=($( sed 's/\\n/ /g' <<< $choices ))

case "$chosen" in
	${list[0]}) nvidia-settings -a [gpu:0]/GpuPowerMizerMode=2 ;;
	${list[1]}) nvidia-settings -a [gpu:0]/GpuPowerMizerMode=0 ;;
	${list[2]}) nvidia-settings -a [gpu:0]/GpuPowerMizerMode=1 ;;
	*) ;;
esac

