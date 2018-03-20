#include "Creature.h"
#include <iostream>

namespace GAME {

	Creature::Creature(
		glm::vec2 pos,
		glm::vec2 size,
		cge::Texture2D * texture,
		cge::AnimationsUV animationsUV,
		bool isSpriteInverted)
		: Entity(pos, size, texture, animationsUV, isSpriteInverted) {}

	void GAME::Creature::interactWithPlayer(Player & player) {
		
		acceleration += (player.position - position);

	}


}


