FROM debian

# Install dependencies
RUN apt-get update
RUN apt-get install build-essential libsdl2-dev libopenal-dev \
                    libpng-dev libjpeg-dev zlib1g-dev mesa-common-dev \
                    liblircclient-dev libcurl4-gnutls-dev \
                    mingw-w64 -y

WORKDIR /q2pro

# Note the order in which we copy:
# we copy from least likely to change to most likely to change.
# this way copied files most likely to change will invalidate as little
# layers as possible
COPY version.sh version.sh
COPY config_win64 .config
COPY static static
COPY Makefile Makefile
COPY inc inc
COPY src src
