#pragma once

#include "Sprite.h"
#include "SpriteSheetUV.h"

#include "SpriteBatch.h"

namespace cge {

	class SpriteSheet : public Sprite {
	public:

		SpriteSheetUV spriteSheetUV;

		SpriteSheet(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, SpriteSheetUV _spriteSheetUV);

		/**
		 * Give to the suppplied SpriteBatch enough informations
		 * to be able to create vertices for this object
		 */
		virtual void drawBatch(cge::SpriteBatch & spriteBatch);

		void time(float delta);
	};

}



