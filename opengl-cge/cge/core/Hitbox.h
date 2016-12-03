#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

namespace cge {

	class Hitbox {
	public:

		/// props
		glm::vec2 position;
		glm::vec2 size;

		/// methods
		/**
		 * Custom constructor with custom size and relative positions
		 */
		Hitbox(glm::vec2 customSize, glm::vec2 customPosition);

		/**
		 * Return whether or not this hitbox intersects with another hitbox
		 * based on two objects positions
		 */
		bool Hitbox::intersects(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position);

	};

}



