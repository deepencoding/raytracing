#!/bin/bash

cd src
g++ -o ../build/debug/main main.cpp 
cd ..
build/debug/main > output/image.ppm
