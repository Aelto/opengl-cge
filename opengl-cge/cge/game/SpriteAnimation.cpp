#include "SpriteAnimation.h"

namespace cge {

	SpriteAnimation::SpriteAnimation(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, AnimationsUV _animationsUV)
		: animationsUV(_animationsUV) {
		position = pos;
		size = _size;
		texture = _texture;

		velocity = glm::vec2(0.0f, 0.0f);
		acceleration = glm::vec2(0.0f, 0.0f);
		inverted = false;

		box = nullptr;
	}

	void SpriteAnimation::batchDraw(cge::SpriteBatch & spriteBatch) {
		if (inverted) {
			spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID,
				animationsUV.getTopRightXUv(), animationsUV.getTopLeftXUv(), animationsUV.getBottomLeftXUv(), animationsUV.getBottomRightXUv(),
				animationsUV.getTopRightYUv(), animationsUV.getTopLeftYUv(), animationsUV.getBottomLeftYUv(), animationsUV.getBottomRightYUv());
		}

		else {
			spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID,
				animationsUV.getTopLeftXUv(), animationsUV.getTopRightXUv(), animationsUV.getBottomRightXUv(), animationsUV.getBottomLeftXUv(),
				animationsUV.getTopLeftYUv(), animationsUV.getTopRightYUv(), animationsUV.getBottomRightYUv(), animationsUV.getBottomLeftYUv());
		}
	}

	void SpriteAnimation::time(float delta) {

		animationsUV.time(delta);

	}
}