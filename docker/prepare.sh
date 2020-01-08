#!/bin/bash
PLATFORM=${1:-all}

if [ $PLATFORM = linux64 ] || [ $PLATFORM = all ] ; then
    # Linux x86_64
    docker build -t q2pro-cc-linux-x86_64 -f ./docker/linux_x86_64/Dockerfile .
fi

if [ $PLATFORM = win64 ] || [ $PLATFORM = all ] ; then
    # Windows x86_64
    docker build -t q2pro-cc-windows-x86_64 -f ./docker/windows_x86_64/Dockerfile .
fi
