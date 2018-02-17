#pragma once
#include <array>

#include <glm/glm.hpp>
#include <cge.h>

#include "../entities/Entity.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 16

namespace GAME {

  class Chunk {
    glm::vec2 position;

    // x:[ y:[ z:[], []], []]
    std::array<
      std::array<
        std::array<
          GAME::Entity,
          CHUNK_HEIGHT>,
        CHUNK_SIZE>,
      CHUNK_SIZE> groundEntities;

    Chunk(int pos_x = 0, int pos_t = 0);

    void translate(int trans_x, int trans_y);

    void translateTo(int trans_x, int trans_y);

  };

}