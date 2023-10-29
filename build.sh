#!/bin/sh

set -xe

dir="build/"

if [ -d "$dir" ]; then
    rm -r "$dir"
fi

mkdir "$dir" && cd "$dir"
cmake ..
make
