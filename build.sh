#!/bin/sh

set -xe

dir="debug/"
target="todo"

if [ -d "$dir" ]; then
    rm -r "$dir"
fi

if [ -d "$target" ]; then
    rm "$target"
fi

mkdir "$dir" && cd "$dir"
cmake ..
make
mv "$target" ../
