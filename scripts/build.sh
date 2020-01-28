#!/bin/bash

CXX=$(which clang++)

rm -rf build
mkdir build
(
    cd build
    cmake ..
    make -j4
)

if [ "$1" = run ] ; then
    (
        cd build
        ./main
    )
fi
