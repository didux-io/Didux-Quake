FROM fedora

# Install dependencies
RUN dnf install @development-tools SDL2-devel openal-soft-devel \
                    libpng-devel libjpeg-devel zlib-devel mesa-libGL-devel \
                    libircclient-devel libcurl-devel wget -y

WORKDIR /q2pro

# Note the order in which we copy:
# we copy from least likely to change to most likely to change.
# this way copied files most likely to change will invalidate as little
# layers as possible
COPY version.sh version.sh
COPY config_linux64 .config
COPY q2pro-mgw-sdk/Makefile libs/
COPY q2pro-mgw-sdk/inc libs/inc
COPY q2pro-mgw-sdk/checksum libs/
COPY Makefile Makefile
COPY inc inc
COPY src src
