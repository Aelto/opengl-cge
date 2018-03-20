#pragma once

#include "Entity.h"

namespace GAME {

	class Player : public Entity {
	public:
		Player(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV);
	};

}