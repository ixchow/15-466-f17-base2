.PHONY : all clean

CPP=g++ -g -Wall -Werror

all : main

clean :
	rm -rf main objs

main : objs/main.o objs/Draw.o
	$(CPP) -o $@ $^ `sdl2-config --libs` -lGL


objs/main.o : main.cpp Draw.hpp GL.hpp glcorearb.h
	mkdir -p objs
	$(CPP) -c -o $@ $< `sdl2-config --cflags`

objs/Draw.o : Draw.cpp Draw.hpp GL.hpp glcorearb.h
	mkdir -p objs
	$(CPP) -c -o $@ $< `sdl2-config --cflags`
