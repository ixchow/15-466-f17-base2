
#include <SDL.h>
#include <iostream>

#define DO(TYPE, NAME) \
	PFNGL ## TYPE ## PROC gl ## NAME = NULL;
#include "gl_shims.hpp"
#undef DO
#undef GL_SHIMS_HPP

bool init_gl_shims() {
	bool failed = false;
	#define DO(TYPE, NAME) \
		gl ## NAME = (PFNGL ## TYPE ## PROC)SDL_GL_GetProcAddress("gl" #NAME); \
		if (!gl ## NAME) { \
			std::cerr << "Error binding "  "gl" #NAME << std::endl; \
			failed = true; \
		}
#include "gl_shims.hpp"
	return !failed;
}
