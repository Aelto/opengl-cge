#pragma once

#include "sprite.h"
#include "animations-uv.h"

#include "spritebatch.h"
#include "sprite-renderer.h"

namespace cge {

	class SpriteAnimation : public Sprite {
	public:
		AnimationsUV animationsUV;

		SpriteAnimation() {};

		SpriteAnimation(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, AnimationsUV _animationsUV)
      : animationsUV(_animationsUV) {
      position = pos;
      size = _size;
      texture = _texture;
      inverted = false;

      box = nullptr;
    }

		/**
		* Give to the suppplied SpriteBatch enough informations
		* to be able to create vertices for this object
		*/
		virtual void batchDraw(cge::SpriteBatch & spriteBatch) {
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

		virtual void draw(cge::SpriteRenderer & spriteRenderer) {   
      if (inverted) {
        spriteRenderer.draw(position.x, position.y, size.x, size.y, texture->ID,
          animationsUV.getTopRightXUv(), animationsUV.getTopLeftXUv(), animationsUV.getBottomLeftXUv(), animationsUV.getBottomRightXUv(),
          animationsUV.getTopRightYUv(), animationsUV.getTopLeftYUv(), animationsUV.getBottomLeftYUv(), animationsUV.getBottomRightYUv(), rotate);
      }

      else {
        spriteRenderer.draw(position.x, position.y, size.x, size.y, texture->ID,
          animationsUV.getTopLeftXUv(), animationsUV.getTopRightXUv(), animationsUV.getBottomRightXUv(), animationsUV.getBottomLeftXUv(),
          animationsUV.getTopLeftYUv(), animationsUV.getTopRightYUv(), animationsUV.getBottomRightYUv(), animationsUV.getBottomLeftYUv(), rotate);
      }
    }

		void time(float delta) {
      animationsUV.time(delta);
    }

		bool inverted;

	};

}