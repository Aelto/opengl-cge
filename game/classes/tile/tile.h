#pragma once

#include "cge.h"

namespace game {

  class Tile : public cge::SpriteAnimation {
    public:
    Tile();
    Tile(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV);
  };

}