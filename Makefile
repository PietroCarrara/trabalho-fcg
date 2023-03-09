./bin/Linux/main: src/main.cpp src/glad.c include/utils.h include/dejavufont.h src/Camera.hpp src/GraphicsManager.hpp  src/InputManager.hpp  src/lowlevel.hpp
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/*.{c,cpp} ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
