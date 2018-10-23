# Debian x86_64
docker build -t q2pro-cc-debian-x86_64 -f ./docker/debian_x86_64/Dockerfile .

# Ubuntu x86_64
docker build -t q2pro-cc-ubuntu-x86_64 -f ./docker/ubuntu_x86_64/Dockerfile .

# Fedora x86_64
docker build -t q2pro-cc-fedora-x86_64 -f ./docker/fedora_x86_64/Dockerfile .

# Windows x86_64
docker build -t q2pro-cc-windows-x86_64 -f ./docker/windows_x86_64/Dockerfile .
