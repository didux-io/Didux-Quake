#!/bin/bash

$(aws ecr get-login --no-include-email --region eu-central-1)

./docker/package.sh linux64

docker build --no-cache -t didux/didux-quake-server:latest .
docker tag didux/didux-quake-server:latest 462619610638.dkr.ecr.eu-central-1.amazonaws.com/didux/didux-quake-server:latest
docker push 462619610638.dkr.ecr.eu-central-1.amazonaws.com/didux/didux-quake-server:latest