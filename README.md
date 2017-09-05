NOTE: please fill in the first section with information about your game.

# *Game Title*

*Game Title* is *Your Name*'s implementation of [*Design Document*](http://graphics.cs.cmu.edu/courses/15-466-f17/game1-designs/put-real-link-here) for game1 in 15-466-f17.

## Build Notes

*Include any special notes or steps required to build your game here. If there are no special notes, delete this section.*

## Asset Pipeline

*Briefly describe the asset pipeline for this game. What sorts of source files are used? How are they processed? How are they loaded?*

## Architecture

*Provide a brief introduction to how you implemented the design. Talk about the basic structure of your code.*

## Reflection

*Reflect on the assignment. What was difficult? What worked well? If you were doing it again, what would you change?*

*Reflect on the design document. What was clear and what was ambiguous? How did you resolve the ambiguities?*


# About Base1

This game is based on Base1, starter code for game1 in the 15-466-f17 course. It was developed by Jim McCann, and is released into the public domain.

## Requirements

 - modern C++ compiler
 - glm
 - libSDL2
 - libpng

On Linux or OSX these requirements should be available from your package manager without too much hassle.

## Building (Local Libraries)

If you are building on a system where you are unable to install libraries, you may wish to use one of the pre-built library repositories:

### Linux

Clone [kit-libs-linux](https://github.com/ixchow/kit-libs-linux) into the `kit-libs-linux` subdirectory:
```
  git clone https://github.com/ixchow/kit-libs-linux
```
Now you can build using the '.local' Makefile:
```
  make -f Makefile.local
```

### OSX

Clone [kit-libs-osx](https://github.com/ixchow/kit-libs-osx) into the `kit-libs-osx` subdirectory:
```
  git clone https://github.com/ixchow/kit-libs-osx
```
Now you can build using the '.local' Makefile:
```
  make -f Makefile.local
```

### Windows

Clone [kit-libs-win](https://github.com/ixchow/kit-libs-win) into the `kit-libs-win` subdirectory:
```
  git clone https://github.com/ixchow/kit-libs-win
```
Now you can:
```
  nmake -f Makefile.win
```
or:
```
  cl.exe /EHsc /W3 /WX /MD /Ikit-libs-win\out\include /Ikit-libs-win\out\include\SDL2 main.cpp Draw.cpp gl_shims.cpp /link /SUBSYSTEM:CONSOLE /LIBPATH:kit-libs-win\out\lib SDL2main.lib SDL2.lib OpenGL32.lib
  copy kit-libs-win\out\dist\SDL2.dll .
```


## Building (System Libraries)

If you are building on a system where you can install libraries easily, then you may wish to build against versions of the required libraries installed by your favorite package manager.

### Linux
```
  g++ -g -Wall -Werror -o main main.cpp Draw.cpp `sdl2-config --cflags --libs` -lGL
```
or:
```
  make
```

### OSX
```
  clang++ -g -Wall -Werror -o main main.cpp Draw.cpp `sdl2-config --cflags --libs`
```
or:
```
  make
```

### Windows

Every scheme I am aware of for "globally installing" libraries on Windows seems like a hack.
