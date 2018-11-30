PLATFORM=${1:-all}

if [ $PLATFORM = debian64 ] || [ $PLATFORM = all ] ; then
    # Debian x86_64
    docker build -t q2pro-cc-debian-x86_64 -f ./docker/debian_x86_64/Dockerfile .
fi

if [ $PLATFORM = ubuntu64 ] || [ $PLATFORM = all ] ; then
    # Ubuntu x86_64
    docker build -t q2pro-cc-ubuntu-x86_64 -f ./docker/ubuntu_x86_64/Dockerfile .
fi

if [ $PLATFORM = fedora64 ] || [ $PLATFORM = all ] ; then
    # Fedora x86_64
    docker build -t q2pro-cc-fedora-x86_64 -f ./docker/fedora_x86_64/Dockerfile .
fi

if [ $PLATFORM = win64 ] || [ $PLATFORM = all ] ; then
    # Windows x86_64
    docker build -t q2pro-cc-windows-x86_64 -f ./docker/windows_x86_64/Dockerfile .
fi
