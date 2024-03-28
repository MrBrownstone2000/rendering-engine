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

echo "add_subdirectory($1)" >> CMakeLists.txt

cp -r projectTemplate $1
cd $1
sed -i "s/@PROJECT/$1/g" CMakeLists.txt
sed -i "/message( FATAL_ERROR /d" CMakeLists.txt

echo "The project was succesfully created!"
