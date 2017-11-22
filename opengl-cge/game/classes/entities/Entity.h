#pragma once

#include <vector>

#include "../../../cge/game/SpriteAnimation.h"
#include "../../../cge/game/AnimationsUV.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

namespace GAME {
	class Entity : public cge::SpriteAnimation {
	public:
		Entity();
		Entity(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV);

		void mainBehavior(GLfloat delta, std::vector<Entity> & collisionEntities);

		float movespeed;
		glm::vec2 oldTranslation;

		/**
		 * Should not be touched manually,
		 * use the acceleration instead if you want to move the element
		 * based on the delta and the movespeed.
		 */
		glm::vec2 velocity;

		glm::vec2 acceleration;

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



