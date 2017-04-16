#pragma once

#include "Sprite.h"
#include "AnimationsUV.h"

#include "../core/SpriteBatch.h"

namespace cge {
	
	class SpriteAnimation : public Sprite {
	public:
		AnimationsUV animationsUV;

		SpriteAnimation(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, AnimationsUV _animationsUV);

		/**
		* Give to the suppplied SpriteBatch enough informations
		* to be able to create vertices for this object
		*/
		virtual void batchDraw(cge::SpriteBatch & spriteBatch);

		void time(float delta);

	};

}