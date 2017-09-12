#include "Scene.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

glm::mat4 Scene::Transform::make_local_to_world() const {
	return glm::mat4( //translate
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(position, 1.0f)
	)
	* glm::mat4_cast(rotation) //rotate
	* glm::mat4( //scale
		glm::vec4(scale.x, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, scale.y, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, scale.z, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

glm::mat4 Scene::Transform::make_world_to_local() const {
	glm::vec3 inv_scale;
	inv_scale.x = (scale.x == 0.0f ? 0.0f : 1.0f / scale.x);
	inv_scale.y = (scale.y == 0.0f ? 0.0f : 1.0f / scale.y);
	inv_scale.z = (scale.z == 0.0f ? 0.0f : 1.0f / scale.z);
	return glm::mat4( //un-scale
		glm::vec4(inv_scale.x, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, inv_scale.y, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, inv_scale.z, 0.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	)
	* glm::mat4_cast(glm::inverse(rotation)) //un-rotate
	* glm::mat4( //un-translate
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(-position, 1.0f)
	);
}

//---------------------------

glm::mat4 Scene::Camera::make_projection() const {
	return glm::infinitePerspective( fovy, aspect, near );
}

//---------------------------

void Scene::render() {
	for (auto const &object : objects) {
		//compute modelview+projection matrix for this object:
		glm::mat4 mvp = 
			camera.make_projection()
			* camera.transform.make_world_to_local()
			* object.transform.make_local_to_world();

		//set up program uniforms:
		glUseProgram(object.program);
		if (object.program_mvp != -1U) {
			glUniformMatrix4fv(object.program_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
		}
		glBindVertexArray(object.vao);

		//draw the object:
		glDrawArrays(GL_TRIANGLES, object.start, object.count);
	}
}
