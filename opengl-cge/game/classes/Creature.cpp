#include "Creature.h"

namespace GAME {

	Creature::Creature(
		glm::vec2 pos,
		glm::vec2 size,
		cge::Texture2D * texture,
		cge::AnimationsUV animationsUV)
		: cge::SpriteAnimation(pos, size, texture, animationsUV) {

	}

	/*void Creature::batchDraw(cge::SpriteBatch & spriteBatch) {
		cge::SpriteAnimation::batchDraw(spriteBatch);
	}*/

}


