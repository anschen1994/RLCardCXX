#!/bin/bash

if [ -d "./build" ]; then
    rm -rf ./build
fi
mkdir build && cd build
cmake ..
make
cp librlcard.so ../lib/
cd ..