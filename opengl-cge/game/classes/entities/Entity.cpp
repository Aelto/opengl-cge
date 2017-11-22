#include "Entity.h"

namespace GAME {
	Entity::Entity() {}

	Entity::Entity(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV)
		: cge::SpriteAnimation(pos, _size, _texture, _animationsUV) {}

	void Entity::mainBehavior(GLfloat delta, std::vector<Entity> & collisionEntities) {

		if (velocity.x < 0)
			inverted = true;
		else inverted = false;

		applyAcceleration(delta);
		applyVelocity(delta);

		for (auto & entity : collisionEntities)
			if (intersects(entity)) {
				acceleration *= 0;
				position -= velocity;
			}

		applyFriction(0.9f);

	}
}

