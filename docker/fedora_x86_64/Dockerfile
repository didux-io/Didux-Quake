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
COPY static static
COPY Makefile Makefile
COPY inc inc
COPY src src
