#!/bin/bash

read -p "Choose the options to use:
	[1] Init a project on github.
	[2] Push files to github.
	" options

case $options in
    1 ) read -p "What is repository name: " name
	echo "# ${name}" >> README.md
	git init
	git add .
	git commit -m "first commit"
	git remote add origin https://github.com/a110605/$name.git
	git push -u origin master
	;;
    2 ) read -p "Enter file name to push (. for all file in dir): " file	
   	read -p "Enter commit for this push: " commit
	git add $file
	git commit -m "${commit}"
	git push
	;;
   * ) echo "Please choose options 1 or 2";
        exit
    	;;
esac
