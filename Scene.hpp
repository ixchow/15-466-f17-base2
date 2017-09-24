#pragma once

#include "GL.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <list>

#undef near //windows.h steps on this

//Describes a 3D scene for rendering:
struct Scene {
	struct Transform {
		Transform() = default;
		Transform(Transform &) = delete;
		~Transform() {
			while (last_child) {
				last_child->set_parent(nullptr);
			}
			if (parent) {
				set_parent(nullptr);
			}
		}

		//simple specification:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); //constructor is w x y z for some reason.
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

		//hierarchy information:
		Transform *parent = nullptr;
		Transform *last_child = nullptr;
		Transform *prev_sibling = nullptr;
		Transform *next_sibling = nullptr;
		//Generally, you shouldn't manipulate the above pointers directly.

		//Add transform to the child list of 'parent', before child 'before':
		void set_parent(Transform *parent, Transform *before = nullptr);

		//helper that checks local pointer consistency:
		void DEBUG_assert_valid_pointers() const;

		//computed from the above:
		glm::mat4 make_local_to_parent() const;
		glm::mat4 make_parent_to_local() const;
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
	};

	Camera camera;
	std::list< Object > objects;
	std::list< Light > lights;

	void render();
};
