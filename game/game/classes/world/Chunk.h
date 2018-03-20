#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <cge.h>

#include "../entities/Entity.h"
#include "../../utils//TextureStorage.h"
#include "../../utils/constants.h"
#include "../../utils/assets-uv.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 16

namespace GAME {

  class Chunk {
    public:
    glm::vec2 position;

    // x:[ y:[ z:[GAME::Entity, ...], [GAME::Entity, ...]], [...]]
    std::vector<std::vector<std::vector<GAME::Entity>>> groundEntities;


    Chunk(int pos_x = 0, int pos_t = 0);

    void generate(Constants & constants, TextureStorage & textureStorage, Assets_uv & assets_uv, cge::Hitbox & wallBox);

    void renderLayer(unsigned int layer, cge::SpriteBatch & spritebatch);

    void renderLayerBelowOrEqual(unsigned int layer, cge::SpriteBatch & spritebatch);

    void translate(int trans_x, int trans_y);

    void translateTo(int trans_x, int trans_y);

  };

}