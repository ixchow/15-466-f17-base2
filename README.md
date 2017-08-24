Base0
=====
Base0 is the starter code for the game0 in the 15-466-f17 course. It was developed by Jim McCann, and is hereby released into the public domain.

Note that Base0 is attempting to illustrate a very straightfoward "get it done" philosophy of game code design -- I've purposefully removed some of the conveniences one typically uses to sweep things under the rug.

This is because game0 *does not need* such conveniences. It is simple because game0 is simple.

Requirements
============
 - glm
 - libSDL2
 - modern C++ compiler

On Linux or OSX these requirements should be available from your package manager without too much hassle.

Building
========
Linux:
  g++ -Wall -Werror -o main main.cpp `sdl2-config --cflags --libs` -lGL

OSX:



