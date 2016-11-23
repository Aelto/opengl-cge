#include "RenderObject.h"

namespace cge {
	RenderObject::RenderObject()
		: position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), size(10.0f, 10.0f), texture(nullptr)
	{}

	RenderObject::RenderObject(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture)
		: position(pos), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), size(size), texture(_texture)
	{}


	void RenderObject::batchDraw(cge::SpriteBatch & spriteBatch)	{

		spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID);

	}


	glm::vec2 RenderObject::distanceTo(const glm::vec2 & pos) {
		
		return glm::vec2( position.x - pos.x, position.y - pos.y );

	}

	bool RenderObject::intersects(const RenderObject & obj) {
		
		return position.x > obj.position.x + obj.size.x
			|| position.y > obj.position.y + obj.size.y
			|| position.x + size.x < obj.position.x
			|| position.y + size.y < obj.position.y;

	}

	void RenderObject::applyAcceleration(const GLfloat delta) {

		velocity.x += acceleration.x;
		velocity.y += acceleration.y;

		acceleration.x = 0;
		acceleration.y = 0;

	}

	void RenderObject::applyVelocity(const GLfloat delta) {

		position.x += velocity.x;
		position.y += velocity.y;

	}
}