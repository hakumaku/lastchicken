#!/usr/bin/env bash

user_files=(
	"$HOME/.vimrc"
	"$HOME/.config/powerline/config.json"
	"$HOME/.tmux.conf"
)

remote_files=(
	"config_file/.vimrc"
	"config_file/config.json"
	"config_file/.tmux.conf"
)

for i in ${!user_files[*]}; do
	file_name=${user_files[$i]##*/}
	printf "Checking ${file_name}: "

	if cmp -s "${user_files[$i]}" "${remote_files[$i]}"; then
		echo "No change in ${file_name}."
	else
		echo "${file_name} has been modified."
		cp ${user_files[$i]} ${remote_files[$i]}
	fi
done

