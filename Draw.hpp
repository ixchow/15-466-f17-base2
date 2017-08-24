#pragma once
/*
 * Draw is a dirt-simple class for getting things drawn in an OpenGL context.
 *
 * All drawing operations use [-1,1] x [-1,1] window coordinates.
 *
 * Example:
 * //draws a red rectangle in the upper right quadrant of the window:
 *   Draw draw;
 *   draw.add_rect(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::u8vec4(0xff, 0x00, 0x00, 0xff));
 *   draw.draw();
 */

#include <vector>
#include <glm/glm.hpp>

struct Draw {
	//add rectangle [min.x,max.x] x [min.y,max.y] in color 'color':
	void add_rectangle(glm::vec2 const &min, glm::vec2 const &max, glm::u8vec4 const &color);
	//draw all rectangles added since last call to draw():
	void draw();

	//----- internals -----
	//simple class for holding on to position + color attribute:
	struct Vertex {
		Vertex(glm::vec2 const &v_, glm::u8vec4 const &c_)
			: v(v_), c(c_) {
		}
		glm::vec2 v;
		glm::u8vec4 c;
	};
	static_assert(sizeof(Vertex) == 12, "Vertex is tightly packed.");
	//list of triangles to draw next call to "draw()":
	std::vector< Vertex > vertices;
};
