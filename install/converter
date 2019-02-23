#!/bin/bash

input=$1

if [[ $# -eq 0 ]]; then
	echo "Input file must be given."
	exit 0
fi

trim_audio () {
	local output
	local from
	local to
	local opt

	echo -n "Output: "
	read output
	local ext="${output##*.}"
	if [[ "$ext" != "mp3" ]]; then
		output+="mp3"
	fi

	echo "1) From ~ To"
	echo "2) From ~ End"
	echo "3) Start ~ To"
	echo "Options: "
	read opt

	case $opt in
		1)
			echo -n "From: "
			read from
			echo -n "To: "
			read to

			ffmpeg -ss $from -to $to -i "$input" -acodec copy "$output"
		;;
		2)
			echo -n "Start: "
			read from
			ffmpeg -ss $from -i "$input" -acodec copy "$output"
		;;
		3)
			echo -n "To: "
			read to
			ffmpeg -t $to -i "$input" -acodec copy "$output"
		;;
		*);;
	esac
}

trim_video () {
	local output
	local from
	local to
	local opt
}

extract_audio () {
	local output

	echo -n "Output: "
	read output
	local ext="${output##*.}"
	if [[ "$ext" != "mp3" ]]; then
		output="${output}.mp3"
	fi

	ffmpeg -i "$input" -f mp3 -vn "$output"
}

clear
while true; do
	echo "Run functions:"
	echo "1) Trim audio"
	echo "2) Trim video"
	echo "3) Extract audio from video"
	echo -e -n "Type number: "
	read opt
	if [[ -z $opt ]]; then
		echo ""
		break;
	fi

	case $opt in
		1) trim_audio;;
		2) trim_video;;
		3) extract_audio;;
		*);;
	esac
done
