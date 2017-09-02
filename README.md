# Base0

Base0 is the starter code for the game0 in the 15-466-f17 course. It was developed by Jim McCann, and is hereby released into the public domain.

Note that Base0 is attempting to illustrate a very straightfoward "get it done" philosophy of game code design -- I've purposefully removed some of the conveniences one typically uses to sweep things under the rug.

This is because game0 *does not need* such conveniences. It is simple because game0 is simple.

## Requirements

 - modern C++ compiler
 - glm
 - libSDL2

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

(TBD -- no local libs package yet)

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
