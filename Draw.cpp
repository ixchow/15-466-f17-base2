#include "Draw.hpp"
#include "GL.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

void Draw::add_rectangle(glm::vec2 const &min, glm::vec2 const &max, glm::u8vec4 const &color) {
	//split rectangle into two triangles, and add both to vertex list:

	vertices.emplace_back(glm::vec2(min.x, min.y), color);
	vertices.emplace_back(glm::vec2(max.x, min.y), color);
	vertices.emplace_back(glm::vec2(max.x, max.y), color);

	vertices.emplace_back(glm::vec2(min.x, min.y), color);
	vertices.emplace_back(glm::vec2(max.x, max.y), color);
	vertices.emplace_back(glm::vec2(min.x, max.y), color);
}

static GLuint compile_shader(GLenum type, std::string const &source);

void Draw::draw() {
	//draw() uses a very simple vertex and fragment shader, which is compiled the first time the draw() function is called.

	//----- initialization code -----

	//attribute locations for program:
	#define program_Position 0
	#define program_Color 1
	static GLuint program = [](){
		GLuint program = 0;

		//STR( program_Position ) evaluates to a quoted version of program_Position, i.e., "0"
		#define STR_( X ) # X
		#define STR( X ) STR_( X )
		GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER,
			"#version 330\n"
			"layout(location = " STR(program_Position) ") in vec4 Position;\n"
			"layout(location = " STR(program_Color) ") in vec4 Color;\n"
			"out vec4 color;\n"
			"void main() {\n"
			"	gl_Position = Position;\n"
			"	color = Color;\n"
			"}\n"
		);

		GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER,
			"#version 330\n"
			"in vec4 color;\n"
			"out vec4 fragColor;\n"
			"void main() {\n"
			"	fragColor = color;\n"
			"}\n"
		);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		//shaders are reference counted so this makes sure they are freed after program is deleted:
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		glLinkProgram(program);
		GLint link_status = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &link_status);
		if (link_status != GL_TRUE) {
			std::cerr << "Failed to link shader program." << std::endl;
			GLint info_log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector< GLchar > info_log(info_log_length, 0);
			GLsizei length = 0;
			glGetProgramInfoLog(program, info_log.size(), &length, &info_log[0]);
			std::cerr << "Info log: " << std::string(info_log.begin(), info_log.begin() + length);
			throw std::runtime_error("failed to link program");
		}
		return program;
	}();

	//we also need a buffer and a VAO to reference said buffer:
	static GLuint buffer = [](){
		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		return buffer;
	}();

	static GLuint vao = [](){
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(program_Position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLbyte *)0);
		glVertexAttribPointer(program_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLbyte *)0 + sizeof(glm::vec2));
		glEnableVertexAttribArray(program_Position);
		glEnableVertexAttribArray(program_Color);
		return vao;
	}();

	//------ actual drawing ------

	//send vertices to graphics card:
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STREAM_DRAW);

	//draw vertices:
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	//clear vertex list:
	vertices.clear();
}

static GLuint compile_shader(GLenum type, std::string const &source) {
	GLuint shader = glCreateShader(type);
	GLchar const *str = source.c_str();
	GLint length = source.size();
	glShaderSource(shader, 1, &str, &length);
	glCompileShader(shader);
	GLint compile_status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE) {
		std::cerr << "Failed to compile shader." << std::endl;
		GLint info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector< GLchar > info_log(info_log_length, 0);
		GLsizei length = 0;
		glGetShaderInfoLog(shader, info_log.size(), &length, &info_log[0]);
		std::cerr << "Info log: " << std::string(info_log.begin(), info_log.begin() + length);
		glDeleteShader(shader);
		throw std::runtime_error("Failed to compile shader.");
	}
	return shader;
}
