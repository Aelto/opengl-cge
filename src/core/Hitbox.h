#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cge {

	class Hitbox {
	public:

		/// props

		/**
		 * This position is relative to the holder's position,
		 * a x position equal to 10 will place the hitbox 10 pixels
		 * on the right of the holder's position
		 */
		glm::vec2 position;

		/**
		 * This allows custom size so the hitbox isn't always equal to
		 * the size of the rendered sprite
		 */
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
		bool intersects(Hitbox * obj, const glm::vec2 & obj1_position, const glm::vec2 & obj2_position, const glm::vec2 & obj1_size, const glm::vec2 & obj2_size);

		/**
		 * Resolve the collision between two hitboxes
		 */
		void resolve(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position);

	};

}



