#!/bin/sh
cd build
cmake ..
make
cd ..
./build/NewUiWt --docroot ./ui --http-address 0.0.0.0 --http-port 8080
