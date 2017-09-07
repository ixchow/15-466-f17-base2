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

all : dist/main

clean :
	rm -rf main objs

dist/main : objs/main.o objs/load_save_png.o
	$(CPP) -o $@ $^ $(SDL_LIBS) -lpng


objs/main.o : main.cpp Draw.hpp GL.hpp glcorearb.h load_save_png.hpp
	mkdir -p objs
	$(CPP) -c -o $@ $< `sdl2-config --cflags`

objs/load_save_png.o : load_save_png.cpp load_save_png.hpp
	mkdir -p objs
	$(CPP) -c -o $@ $<
