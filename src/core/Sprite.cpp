#include "Sprite.h"

namespace cge {
	Sprite::Sprite()
		: position(0.0f, 0.0f), size(10.0f, 10.0f), texture(nullptr), box(nullptr) {}

	Sprite::Sprite(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture)
		: position(pos), size(size), texture(_texture), box(nullptr) {}


	void Sprite::drawBatch(cge::SpriteBatch & spriteBatch) {

		spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID);

	}


	glm::vec2 Sprite::distanceTo(const glm::vec2 & pos) {

		return glm::vec2(position.x - pos.x, position.y - pos.y);

	}

	bool Sprite::intersects(const Sprite & obj) {
		if (box == nullptr)
			return false;

		return box->intersects(obj.box, position, obj.position, size, obj.size);
	}

	void Sprite::resolve(Sprite & obj) {

		box->resolve(obj.box, position, obj.position);

	}

	void Sprite::addBox(Hitbox * _box) {

		box = _box;

	}
}