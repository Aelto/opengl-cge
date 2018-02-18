#pragma once

#include "Sprite.h"
#include "AnimationsUV.h"

#include "SpriteBatch.h"
#include "SpriteRenderer.h"

namespace cge {

	class SpriteAnimation : public Sprite {
	public:
		AnimationsUV animationsUV;

		SpriteAnimation() {};

		SpriteAnimation(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, AnimationsUV _animationsUV);

		/**
		* Give to the suppplied SpriteBatch enough informations
		* to be able to create vertices for this object
		*/
		virtual void drawBatch(cge::SpriteBatch & spriteBatch);

		virtual void draw(cge::SpriteRenderer & spriteRenderer);

		void time(float delta);

		bool inverted;

	};

}