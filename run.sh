#!/bin/bash

mkdir -p build
mkdir -p build/debug
cmake -DCMAKE_BUILD_TYPE=Debug .
cmake -B build/debug
cmake --build build/debug
build/debug/raytracing > output/image.ppm
open output/image.ppm
