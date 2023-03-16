#!/bin/bash

run() {
	cd bin/Linux/
	./main
	cd ../..
}

mkdir -p bin/Linux
g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/*.{c,cpp} ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor && run
