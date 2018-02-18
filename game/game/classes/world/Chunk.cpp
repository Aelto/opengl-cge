#include "Chunk.h"

namespace GAME {

  Chunk::Chunk(int pos_x, int pos_y)
    : position(pos_x, pos_y) {
    


  }

  void Chunk::translate(int trans_x, int trans_y) {

    for (int x = 0; x < CHUNK_SIZE; x++)
      for (int y = 0; y < CHUNK_SIZE; y++)
        for (int z = 0; z < CHUNK_HEIGHT; z++) {
          groundEntities[x][y][z].position.x += trans_x;
          groundEntities[x][y][z].position.y += trans_y;
        }

  }

  void Chunk::translateTo(int trans_x, int trans_y) {
    translate(trans_x - position.x, trans_y - position.y);
  }

  void Chunk::generate(Constants & constants, TextureStorage & textureStorage, Assets_uv & assets_uv, cge::Hitbox & wallBox) {
    // TODO: better generation
    for (unsigned int x = 0; x < CHUNK_SIZE; x += 1)
			for (unsigned int y = 0; y < CHUNK_SIZE; y += 1) 
        for (unsigned int z = 0; z < CHUNK_HEIGHT; z += 1) {
          groundEntities[x][y][z] = GAME::Entity(
              glm::vec2(x * constants.tile_size, y * constants.tile_size),
              glm::vec2(constants.tile_size, constants.tile_size),
              &textureStorage.assetsPNG,
              assets_uv.FLOORS[5]
            );
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