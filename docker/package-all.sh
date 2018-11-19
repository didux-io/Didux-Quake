# Make sure all builds are run
./docker/build-all.sh

# Package Debian x86_64
tar -cvzf debian_x86_64.tar.gz ./output/debian/x86_64

# # Package Ubuntu x86_64
# mkdir -p ./output/ubuntu/x86_64
# docker run --mount src="$(pwd)/output/ubuntu/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-ubuntu-x86_64 /usr/bin/make

# # Package Fedora x86_64
# mkdir -p ./output/fedora/x86_64
# docker run --mount src="$(pwd)/output/fedora/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-fedora-x86_64 /usr/bin/make

# # Package Windows x86_64
# mkdir -p ./output/windows/x86_64
# docker run --mount src="$(pwd)/output/windows/x86_64",target=/q2pro/output,type=bind -it q2pro-cc-windows-x86_64 /usr/bin/make
