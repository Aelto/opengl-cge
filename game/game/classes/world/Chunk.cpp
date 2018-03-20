#include "Chunk.h"

namespace GAME {

  Chunk::Chunk(int pos_x, int pos_y)
    : position(pos_x, pos_y) {
    
    groundEntities.resize(CHUNK_SIZE);
    for (std::vector<std::vector<GAME::Entity>> & x_vector : groundEntities) {
      
      x_vector.resize(CHUNK_SIZE);
      for (std::vector<GAME::Entity> & y_vector : x_vector) {

        y_vector.resize(CHUNK_HEIGHT);
      }
    }

  }

  void Chunk::translate(int trans_x, int trans_y) {
    for (auto & x_vector : groundEntities) {
      for (auto & y_vector : x_vector) {
        for (auto & entity : y_vector) {
          entity.position.x += trans_x;
          entity.position.x += trans_y;
        }
      }
    }
  }

  void Chunk::translateTo(int trans_x, int trans_y) {
    translate(trans_x - position.x, trans_y - position.y);
  }

  void Chunk::generate(Constants & constants, TextureStorage & textureStorage, Assets_uv & assets_uv, cge::Hitbox & wallBox) {
    // TODO: better generation
    
    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
      for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
        for (unsigned int z = 0; z < CHUNK_HEIGHT; z += 1) {
          groundEntities[x][y][z] = GAME::Entity(
              glm::vec2(x * constants.tile_size + position.x, y * constants.tile_size + position.y),
              glm::vec2(constants.tile_size, constants.tile_size),
              &textureStorage.assetsPNG,
              assets_uv.FLOORS[5]
            );
        }
      }
    }
    for (auto & x_vector : groundEntities) {
      for (auto & y_vector : x_vector) {
        
      }
    }
  }

  void Chunk::renderLayer(unsigned int layer, cge::SpriteBatch & spritebatch) {
    layer = layer % CHUNK_HEIGHT;

    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
      for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
        groundEntities[x][y][layer].drawBatch(spritebatch);
      }
    }
  }

  void Chunk::renderLayerBelowOrEqual(unsigned int layer, cge::SpriteBatch & spritebatch) {
    layer = layer % CHUNK_HEIGHT;

    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
      for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
        for (; layer >= 0; layer--) {
          groundEntities[x][y][layer].drawBatch(spritebatch);
        }
      }
    }
  }

}