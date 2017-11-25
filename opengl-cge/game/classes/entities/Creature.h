#pragma once

#include "../../../cge/cge.h"
#include "Entity.h"
#include "Player.h"

namespace GAME {

	class Creature : public Entity {
	public:
		Creature(glm::vec2 pos, glm::vec2 size, cge::Texture2D * texture, cge::AnimationsUV animationsUV, bool isSpriteInverted = false);

		void interactWithPlayer(Player & player);
	};

}