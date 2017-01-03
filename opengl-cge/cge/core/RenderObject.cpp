#include "RenderObject.h"

namespace cge {
	RenderObject::RenderObject()
		: position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), size(10.0f, 10.0f), texture(nullptr), box(nullptr)
	{}

	RenderObject::RenderObject(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture)
		: position(pos), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), size(size), texture(_texture), box(nullptr)
	{}


	void RenderObject::batchDraw(cge::SpriteBatch & spriteBatch)	{

		spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID);

	}


	glm::vec2 RenderObject::distanceTo(const glm::vec2 & pos) {
		
		return glm::vec2( position.x - pos.x, position.y - pos.y );

	}

	bool RenderObject::intersects(const RenderObject & obj) {

		if (box == nullptr)
			return false;
	
		return box->intersects(obj.box, position, obj.position);

	}

	void RenderObject::resolve(RenderObject & obj) {

		box->resolve(obj.box, position, obj.position);

	}

	void RenderObject::addBox(Hitbox * _box) {

		box = _box;

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

		oldTranslation.x = velocity.x;
		oldTranslation.y = velocity.y;

	}

	void RenderObject::applyFriction(const GLfloat factor)	{
		velocity *= factor;
	}
}