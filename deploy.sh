#!/bin/bash

$(aws ecr get-login --no-include-email --region eu-west-1)

./docker/package.sh debian64

docker build --no-cache -t smilo/smilo-quake-server:latest .
docker tag smilo/smilo-quake-server:latest 462619610638.dkr.ecr.eu-west-1.amazonaws.com/smilo/smilo-quake-server:latest
docker push 462619610638.dkr.ecr.eu-west-1.amazonaws.com/smilo/smilo-quake-server:latest