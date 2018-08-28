#!/bin/sh

cd ./build
make clean
make
cd ..
./build/HeaderWt --docroot . --http-address 0.0.0.0 --http-port 8080
