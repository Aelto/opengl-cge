#include "Entity.h"

#include <iostream>

namespace GAME {
	Entity::Entity()
		: velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f) {}

	Entity::Entity(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV, bool isSpriteInverted)
		: cge::SpriteAnimation(pos, _size, _texture, _animationsUV), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), movespeed(1.0f) {
		this->isSpriteInverted = isSpriteInverted;
	}

	void Entity::mainBehavior(GLfloat delta, std::vector<Entity> & collisionEntities) {

		if (velocity.x < 0)
			inverted = !isSpriteInverted;
		else inverted = isSpriteInverted;

		applyAcceleration(delta);
		applyVelocity(delta);

		for (auto & entity : collisionEntities)
			if (intersects(entity)) {
				position.x -= velocity.x;
				position.y -= velocity.y;
			}

		applyFriction(0.9f);

	}

	void Entity::applyAcceleration(const GLfloat delta) {

		if (glm::length(acceleration) != 0) {

			acceleration /= glm::length(acceleration);

			velocity.x += acceleration.x * delta * movespeed;
			velocity.y += acceleration.y * delta * movespeed;

			acceleration.x = 0;
			acceleration.y = 0;
		}

	}

	void Entity::applyVelocity(const GLfloat delta) {

		position.x += velocity.x;
		position.y += velocity.y;

		oldTranslation.x = velocity.x;
		oldTranslation.y = velocity.y;

	}

	void Entity::applyFriction(const GLfloat factor) {
		velocity *= factor;
	}
}

