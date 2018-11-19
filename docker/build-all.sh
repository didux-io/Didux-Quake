# Make sure all containers are build and up to date
./docker/prepare.sh

# Build Debian x86_64
mkdir -p ./output/debian/x86_64
docker run --mount src="$(pwd)/output/debian/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-debian-x86_64 /usr/bin/make

# Build Ubuntu x86_64
mkdir -p ./output/ubuntu/x86_64
docker run --mount src="$(pwd)/output/ubuntu/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-ubuntu-x86_64 /usr/bin/make

# Build Fedora x86_64
mkdir -p ./output/fedora/x86_64
docker run --mount src="$(pwd)/output/fedora/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-fedora-x86_64 /usr/bin/make

# Build Windows x86_64
mkdir -p ./output/windows/x86_64
docker run --mount src="$(pwd)/output/windows/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-windows-x86_64 /usr/bin/make

# Build Darwin x86_64
make all CONFIG_FILE=./config_darwin
