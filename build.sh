#!/bin/sh

set -xe

dir="build/"

if [ ! -d "$dir" ]; then
    mkdir "$dir"
fi

cd "$dir"
cmake ..
make
