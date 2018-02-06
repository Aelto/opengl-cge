#pragma once

#include "../../src/cge.h"

namespace GAME {

	class EntityBuilder {

	public:
		EntityBuilder(GameInstance * gameInstance) {
			gameInstance = gameInstance;
		};

		static cge::SpriteAnimation horizWall(
			GameInstance & gameInstance,
			int x = 0,
			int y = 0,
			int width = gameInstance->constants.tile_size,
			int height = gameInstance->constants.tile_size) {

			return cge::SpriteAnimation(
				glm::vec2(x, y),
				glm::vec2(width, height),
				&gameInstance->textureStorage.assetsPNG,
				gameInstance->assets_uv::WALLS[0]);
		}
	};

}