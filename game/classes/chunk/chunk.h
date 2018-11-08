#pragma once

#include <vector>
#include "../tile/tile.h"

namespace game {

  class Chunk {
    public:
    Chunk(unsigned int dimension, cge::Texture2D & texture, unsigned int x, unsigned int y);

    unsigned int width;
    unsigned int height;
    std::vector<game::Tile> tiles;

  };

}