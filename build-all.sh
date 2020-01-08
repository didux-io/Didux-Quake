#!/bin/bash

cp ./config_darwin ./.config
make clean
make

cp ./config_linux64 ./.config
make clean
make

cp ./config_win64 ./.config
make clean
make