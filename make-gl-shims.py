#!/usr/bin/env python3

#create gl_shims.hpp by parsing everything from glcorearb.h (why not the regsistry xml, hmmmm?) and selecting only things that are core through version 3_3.

import re

protos = []
extensions = []

with open('glcorearb.h', 'r') as f:
	in_version = None
	for line in f:
		m = re.match(r"^#ifndef (GL_VERSION_(\d)_(\d))", line)
		if m != None:
			assert(in_version == None)
			in_version = m.group(1)
			major = int(m.group(2))
			minor = int(m.group(3))
			if (major,minor) < (1,1):
				protos.append("\n// " + in_version + " prototypes:\n")
				do_proto = True
				do_extension = False
			elif (major,minor) < (3,3):
				extensions.append("\n// " + in_version + " extensions:\n")
				do_proto = False
				do_extension = True
			else:
				do_proto = False
				do_extension = False
		if in_version:
			if do_proto:
				m = re.match(r"^GLAPI ", line)
				if m != None:
					protos.append(line)
				pass
			if do_extension:
			#	m = re.match(r".* PFNGL([^)]+)PROC\)", line)
				m = re.match(r"GLAPI .* APIENTRY gl([^ ]+) \(", line)
				if m != None:
					lc = m.group(1)
					uc = lc.upper()
					extensions.append("DO(" + uc + ", " + lc + ")\n")
				pass
			m = re.match(r"^#endif /\* " + in_version + " \*/$", line)
			if m != None:
				in_version = None

print("""#ifndef GL_SHIMS_HPP
#define GL_SHIMS_HPP 1

#ifndef PROTOTYPES
#define PROTOTYPES 1
#include "glcorearb.h"

bool init_gl_shims();
//Prototypes for 1.0,1.1 functionality, pretty sure that already exists:

extern "C" {
""")

print("".join(protos))

print("""
}

#endif //PROTOTYPES

//--------------------------------------------------------

#ifndef DO
#define DO(TYPE, NAME) \
	extern PFNGL ## TYPE ## PROC gl ## NAME;
#endif

""")

print("".join(extensions))

print("#endif //GL_SHIMS_HPP")
