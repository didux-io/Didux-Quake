FROM debian

# Install dependencies
RUN apt-get update
RUN apt-get install build-essential libsdl2-dev libopenal-dev \
                    libpng-dev libjpeg-dev zlib1g-dev mesa-common-dev \
                    liblircclient-dev libcurl4-gnutls-dev wget coreutils -y

RUN useradd -ms /bin/bash quake

WORKDIR /q2pro

RUN chown -R quake:quake /q2pro

USER quake

COPY ./output/debian_x86_64.tar.gz .

RUN tar -zxf debian_x86_64.tar.gz

ENTRYPOINT ./SmiloQuakeDedicated $QUAKE_ARGS