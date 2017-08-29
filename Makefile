.PHONY : all clean

UNAME=$(shell uname -s)
ifeq ($(UNAME),Darwin)
	#OSX/llvm
	CPP=clang++ -std=c++14 -g -Wall -Werror
	SDL_LIBS=`sdl2-config --libs` -framework OpenGL
else
	#assume Linux/g++
	CPP=g++ -g -Wall -Werror
	SDL_LIBS=`sdl2-config --libs` -lGL
endif

all : main

clean :
	rm -rf main objs

main : objs/main.o objs/Draw.o
	$(CPP) -o $@ $^ $(SDL_LIBS)


objs/main.o : main.cpp Draw.hpp GL.hpp glcorearb.h
	mkdir -p objs
	$(CPP) -c -o $@ $< `sdl2-config --cflags`

objs/Draw.o : Draw.cpp Draw.hpp GL.hpp glcorearb.h
	mkdir -p objs
	$(CPP) -c -o $@ $< `sdl2-config --cflags`
