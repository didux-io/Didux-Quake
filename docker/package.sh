PLATFORM=${1:-all}

# Make sure all builds are run
./docker/build.sh $PLATFORM

# Remove previous packages
rm ./output/*.tar.gz

if [ $PLATFORM = debian64 ] || [ $PLATFORM = all ] ; then
    # Package Debian x86_64
    tar -cvzf ./output/debian_x86_64.tar.gz -C ./output/debian/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json
fi

if [ $PLATFORM = ubuntu64 ] || [ $PLATFORM = all ] ; then
    # Package Ubuntu x86_64
    tar -cvzf ./output/ubuntu_x86_64.tar.gz -C ./output/ubuntu/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json
fi

if [ $PLATFORM = fedora64 ] || [ $PLATFORM = all ] ; then
    # Package Fedora x86_64
    tar -cvzf ./output/fedora_x86_64.tar.gz -C ./output/fedora/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json
fi

if [ $PLATFORM = win64 ] || [ $PLATFORM = all ] ; then
    # Package Windows x86_64
    tar -cvzf ./output/windows_x86_64.tar.gz -C ./output/windows/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json
fi

if [ $PLATFORM = darwin64 ] || [ $PLATFORM = all ] ; then
    # Package Darwin x86_64
    tar -cvzf ./output/darwin_x86_64.tar.gz -C ./output/darwin/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json
fi
