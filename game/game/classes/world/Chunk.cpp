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

  }

}