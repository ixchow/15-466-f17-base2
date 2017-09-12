#pragma once

#include "GL.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

//Describes a 3D scene for rendering:
struct Scene {
	struct Transform {
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

		//computed from the above:
		glm::mat4 make_local_to_world() const;
		glm::mat4 make_world_to_local() const;
	};
	struct Camera {
		Transform transform;
		//camera parameters (perspective):
		float fovy = glm::radians(60.0f); //vertical fov (in radians)
		float aspect = 1.0f; //x / y
		float near = 0.01f; //near plane
		//computed from the above:
		glm::mat4 make_projection() const;
	};
	struct Object {
		Transform transform;
		//geometric info:
		GLuint vao = 0;
		GLuint start = 0;
		GLuint count = 0;
		//program info:
		GLuint program = 0;
		GLuint program_mvp = -1U; //uniform index for MVP matrix
		GLuint program_itmv = -1U; //uniform index for inverse(transpose(mv)) matrix
	};
	struct Light {
		Transform transform;
		//light parameters (directional):
		glm::vec3 intensity = glm::vec3(1.0f, 1.0f, 1.0f); //effectively, color
		glm::vec3 direction = glm::vec3(0.0f,-1.0f, 0.0f);
	};

	Camera camera;
	std::vector< Object > objects;
	std::vector< Light > lights;

	void render();
};
