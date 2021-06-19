#!/bin/bash

if [ -d "./build" ]; then
    rm -rf ./build
fi
mkdir build && cd build
if [ "$1" == "debug" ]
then
    cmake .. -DCMAKE_BUILD_TYPE=Debug
else
    cmake .. -DCMAKE_BUILD_TYPE=Release
fi 
make
cd ..