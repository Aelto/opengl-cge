#include "tile.h"

namespace game {

  Tile::Tile() {}

	Tile::Tile(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV)
		: cge::SpriteAnimation(pos, _size, _texture, _animationsUV) {
	}
}