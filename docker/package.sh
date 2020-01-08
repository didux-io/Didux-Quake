#!/bin/bash
PLATFORM=${1:-all}

# Make sure all builds are run
./docker/build.sh $PLATFORM

# Remove previous packages
rm -f ./output/*.tar.gz

# IMPORTANT! The order in which the contents are put into the tar.gz matter!
# Don't just go switching around this order... you will most likely break things.
# Why? When building locally (e.g. simply running `make`) a game library will be added to the ./baseq2 directory.
# This locally build library will be copied into the tar and will then be overwritten by the correct game library.
# This will only happen if the current tar order is maintained!

if [ $PLATFORM = linux64 ] || [ $PLATFORM = all ] ; then
    # Package Linux x86_64
    tar -czf ./output/linux_x86_64.tar.gz -C . ./baseq2  -C ./output/linux/x86_64 . -C ../../../ ./manifest.json
fi

if [ $PLATFORM = win64 ] || [ $PLATFORM = all ] ; then
    # Package Windows x86_64
    tar -czf ./output/windows_x86_64.tar.gz -C . ./baseq2  -C ./output/windows/x86_64 . -C ../../../ ./manifest.json
fi

if [ $PLATFORM = darwin64 ] || [ $PLATFORM = all ] ; then
    # Package Darwin x86_64
    tar -czf ./output/darwin_x86_64.tar.gz -C . ./baseq2  -C ./output/darwin/x86_64 . -C ../../../ ./manifest.json
fi
