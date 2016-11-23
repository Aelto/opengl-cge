#include "RenderObject.h"

namespace wip {


	void RenderObject::draw(cge::SpriteBatch & spriteBatch)	{

		spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID);

	}


	glm::vec2 RenderObject::distanceTo(glm::vec2 pos) {
		return glm::vec2();
	}

	bool RenderObject::intersects(RenderObject & obj) {
		return false;
	}
	void RenderObject::calculateGravity(RenderObject & planet) {
	}

	void RenderObject::applyAcceleration(GLfloat delta) {
	}

	void RenderObject::applyVelocity(GLfloat delta) {
	}
}