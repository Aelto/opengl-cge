#include "Room.h"

#include "../../utils/constants.h"

namespace GAME {
	Room::Room(int size_x, int size_y, int pos_x, int pos_y)
		: size(size_x, size_y), position(pos_x, pos_y) {}

	void Room::generate(Constants & constants, TextureStorage & textureStorage, Assets_uv & assets_uv, cge::Hitbox & wallBox) {
		
		// ground entities
		for (auto x = 0; x < size.x; x += 1)
			for (auto y = 0; y < size.y; y += 1) {
				groundEntities.push_back(
					GAME::Entity(
						glm::vec2(x * constants.tile_size, y * constants.tile_size),
						glm::vec2(constants.tile_size, constants.tile_size),
						&textureStorage.assetsPNG,
						assets_uv.FLOORS[5]
					)
				);
			}

		// top walls
		for (auto x = 0; x < size.x; x += 2) {
			wallEntities.push_back(
				GAME::Entity(
					glm::vec2(x * constants.tile_size, size.y * constants.tile_size),
					glm::vec2(constants.tile_size * 2, constants.tile_size * 2),
					&textureStorage.assetsPNG,
					assets_uv.WALLS[0]
				)
			);

			wallEntities.back().addBox(&wallBox);
		}
	}

	void Room::render(cge::SpriteBatch & batch) {

		for (auto & entity : groundEntities)
			entity.batchDraw(batch);

		for (auto & entity : wallEntities)
			entity.batchDraw(batch);

		for (auto & entity : entities)
			entity.batchDraw(batch);

	}

	void Room::intersects(GLfloat delta, GAME::Entity & entity) {
	
		for (auto & wall : wallEntities) {
			if (entity.intersects(wall)) {
				entity.position.x -= entity.velocity.x;
				entity.position.y -= entity.velocity.y;
			}
		}

	}

}