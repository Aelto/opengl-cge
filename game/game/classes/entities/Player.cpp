#include "Player.h"

namespace GAME {

	Player::Player(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV)
	: Entity(pos, _size, _texture, _animationsUV) {}

}