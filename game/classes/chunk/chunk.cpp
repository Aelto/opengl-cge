#include "chunk.h"

#include "../../utils/constants.h"

namespace game {

  Chunk::Chunk(unsigned int dimension, cge::Texture2D & texture, unsigned int x = 0, unsigned int y = 0) {

    auto uvCoordinates = cge::AnimationsUV(31, 57)
			.setAnimation(std::string("default"), 5, 0, 16, 16, 1000);

    tiles.resize(dimension * dimension);

    unsigned int current_x = 0;
    unsigned int current_y = 0;

    for (auto i = 0; i < dimension * dimension; i++) {
      tiles[i] = game::Tile(
        glm::vec2((x + current_x) * TILE_SIZE, (y + current_y) * TILE_SIZE),
        glm::vec2(TILE_SIZE, TILE_SIZE),
        &texture,
        uvCoordinates
      );

      current_x += 1;

      if (current_x >= dimension) {
        current_x = 0;
        current_y += 1;
      }
    }

  }

}