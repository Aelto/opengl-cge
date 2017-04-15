#include "SpriteSheet.h"

#include <iostream>

namespace cge {

	SpriteSheet::SpriteSheet(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, SpriteSheetUV _spriteSheetUV)
		: spriteSheetUV(_spriteSheetUV) {
		position = pos;
		size = _size;
		texture = _texture;

		velocity = glm::vec2(0.0f, 0.0f);
		acceleration = glm::vec2(0.0f, 0.0f);
		
		box = nullptr;
	}

	void SpriteSheet::batchDraw(cge::SpriteBatch & spriteBatch)	{
		spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID,
			spriteSheetUV.getTopLeftXUv(), spriteSheetUV.getTopRightXUv(), spriteSheetUV.getBottomRightXUv(), spriteSheetUV.getBottomLeftXUv(),
			spriteSheetUV.getTopLeftYUv(), spriteSheetUV.getTopRightYUv(), spriteSheetUV.getBottomRightYUv(), spriteSheetUV.getBottomLeftYUv());
	}

	void SpriteSheet::time(float delta) {

		spriteSheetUV.time(delta);

	}

}

