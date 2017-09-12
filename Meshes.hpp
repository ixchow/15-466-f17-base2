#pragma once

#include "GL.hpp"
#include <map>

//Mesh is a lightweight handle to some OpenGL vertex data:
struct Mesh {
	GLuint vao = 0;
	GLuint start = 0;
	GLuint count = 0;
};

//"Meshes" loads a collection of meshes and builds VAOs for 'em
// you pass in a 'Bindings' object to specify which attributes to bind where

struct Meshes {
	struct Attributes {
		GLuint Position = -1U;
		GLuint Normal = -1U;
	};
	//add meshes from a file; use the indicated indices for attribute locations:
	// note: will throw if file fails to read.
	void load(std::string const &filename, Attributes const &attributes);

	//look up a particular mesh in the DB:
	// note: will throw if mesh not found.
	Mesh const &get(std::string const &name) const;

	//internals:
	std::map< std::string, Mesh > meshes;
};
