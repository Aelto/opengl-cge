#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "../core/Texture.h"
#include "../core/Shader.h"
#include "../core/SpriteBatch.h"
#include "Hitbox.h"

namespace cge {

	class Sprite {
	public:
		Sprite();
		Sprite(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture);

		/// props
		glm::vec2 position;

		glm::vec2 size;

		glm::vec3 color;

		GLfloat rotate;

		cge::Texture2D * texture;

		cge::Hitbox * box;

		/// methods

		/**
		 * Give to the suppplied SpriteBatch enough informations
		 * to be able to create vertices for this object
		 */
		virtual void batchDraw(cge::SpriteBatch & spriteBatch);

		/**
		 * Get a glm::vec2 with the distance relative to this->position
		 * between this->position and another glm::vec2
		 */
		glm::vec2 distanceTo(const glm::vec2 & pos);

		/**
		 * Get whether or not "this" does intersect
		 * with another Sprite
		 */
		bool intersects(const Sprite & obj);

		/**
		 * Resolve the collision so "this" and "obj" don't
		 * touch anymore by moving "this"
		 */
		void resolve(Sprite & obj);

		/**
		 * Create a list of boxes based on the data supplied
		 * It needs a vector of relative positions and a vector of sizes,
		 * these two vectors must have the same size
		 */
		void addBox(Hitbox * _box);

		

	};

}