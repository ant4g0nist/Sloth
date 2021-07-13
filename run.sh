#!/bin/bash
image="sloth:v1"
docker build -t $image .
docker run --rm -v `pwd`/resources/rootfs:/rootfs -v `pwd`/resources/examples:/examples -it $image bash