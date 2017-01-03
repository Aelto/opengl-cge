#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "Texture.h"
#include "Shader.h"
#include "SpriteBatch.h"
#include "Hitbox.h"

namespace cge {

	class RenderObject {
	public:
		RenderObject();
		RenderObject(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture);

		/// props
		glm::vec2 position;
		glm::vec2 oldTranslation;
		glm::vec2 velocity;
		glm::vec2 acceleration;

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
		 * with another RenderObject
		 */
		bool intersects(const RenderObject & obj);

		/**
		 * Resolve the collision so "this" and "obj" don't
		 * touh anymore by moving "this"
		 */
		void resolve(RenderObject & obj);

		/**
		 * Create a list of boxes based on the data supplied
		 * It needs a vector of relative positions and a vector of sizes,
		 * these two vectors must have the same size
		 */
		void addBox(Hitbox * _box);

		/**
		 * Add the value of this->acceleration to this->velocity
		 * then resets the acceleration value.
		 * It should be called before this->applyVelocity()
		 */
		void applyAcceleration(const GLfloat delta);

		/**
		 * Add the value of this->velocity to this->position.
		 * It should be called just before this->draw()
		 */
		void applyVelocity(const GLfloat delta);

		/**
		 * Multiply the velocity by the factor
		 */
		void applyFriction(const GLfloat factor);

	};

}