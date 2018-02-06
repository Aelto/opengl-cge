#pragma once

#include "sprite.h"
#include "spritesheet-uv.h"

#include "spritebatch.h"

namespace cge {

	class SpriteSheet : public Sprite {
	public:

		SpriteSheetUV spriteSheetUV;

		SpriteSheet(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, SpriteSheetUV _spriteSheetUV)
      : spriteSheetUV(_spriteSheetUV) {
      position = pos;
      size = _size;
      texture = _texture;

      box = nullptr;
	}

		/**
		 * Give to the suppplied SpriteBatch enough informations
		 * to be able to create vertices for this object
		 */
		virtual void batchDraw(cge::SpriteBatch & spriteBatch) {
      spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID,
        spriteSheetUV.getTopLeftXUv(), spriteSheetUV.getTopRightXUv(), spriteSheetUV.getBottomRightXUv(), spriteSheetUV.getBottomLeftXUv(),
        spriteSheetUV.getTopLeftYUv(), spriteSheetUV.getTopRightYUv(), spriteSheetUV.getBottomRightYUv(), spriteSheetUV.getBottomLeftYUv());
    }

		void time(float delta) {
      spriteSheetUV.time(delta);
    }
	};

}

