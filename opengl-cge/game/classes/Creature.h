#pragma once

#include "../../cge/cge.h"

#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

namespace GAME {

	class Creature : public cge::SpriteAnimation {
	public:
		Creature(glm::vec2 pos, glm::vec2 size, cge::Texture2D * texture, cge::AnimationsUV animationsUV);

		//void batchDraw(cge::SpriteBatch & spriteBatch);

		// void interact();
	};

}