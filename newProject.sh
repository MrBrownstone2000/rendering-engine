#! /usr/bin/bash

set -e

if (( $# != 1 )); then
    >&2 echo "Error: wrong arguments"
    >&2 echo "Usage: " $0 "<projectName>"
    exit 1
fi

if [[ -f $1 || -d $1 ]]; then
    >&2 echo "Error: the project already exists !"
    exit 1
fi

cp -r projectTemplate $1
cd $1
sed -i "s/@PROJECT/$1/g" Makefile
sed -i "/(error /d" Makefile

echo "The project was succesfully created!"
echo "You can now add the name of the project to the project list at the top of the main Makefile"
