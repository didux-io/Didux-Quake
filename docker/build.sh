#!/bin/bash
PLATFORM=${1:-all}

# Make sure all containers are build and up to date
./docker/prepare.sh $PLATFORM

# Clean previous build output
rm -rf ./output/*/

if [ $PLATFORM = linux64 ] || [ $PLATFORM = all ] ; then
    # Build Linux x86_64
    mkdir -p ./output/linux/x86_64
    docker run --mount src="$(pwd)/output/linux/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-linux-x86_64 //usr/bin/make
fi

if [ $PLATFORM = win64 ] || [ $PLATFORM = all ] ; then
    # Build Windows x86_64
    mkdir -p ./output/windows/x86_64
    docker run --mount src="$(pwd)/output/windows/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-windows-x86_64 //usr/bin/make
fi

if [ $PLATFORM = darwin64 ] || [ $PLATFORM = all ] ; then
    # Build Darwin x86_64
    make clean CONFIG_FILE=./config_darwin
    make all CONFIG_FILE=./config_darwin
fi
