FROM ubuntu:trusty

# Install dependencies
RUN apt-get update
RUN apt-get install build-essential libopenal-dev libsdl2-2.0-0 libglu1-mesa-dev libgles2-mesa-dev libsdl2-dev \
                    mesa-common-dev \
                    liblircclient-dev wget coreutils -y

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
