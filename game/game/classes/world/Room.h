#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "cge.h"
#include "../entities/Entity.h"
#include "../../utils//TextureStorage.h"
#include "../../utils/constants.h"
#include "../../utils/assets-uv.h"

namespace GAME {

	class Room {
	public:
		Room(int size_x, int size_y, int pos_x, int pos_y);

		void generate(Constants & constants, TextureStorage & textureStorage, Assets_uv & assets_uv, cge::Hitbox & wallBox);

		void render(cge::SpriteBatch & batch);
		
		void intersects(GLfloat delta, GAME::Entity & entity);

		glm::vec2 size;

		glm::vec2 position;

		std::vector<Entity> groundEntities;

		std::vector<Entity> wallEntities;

		std::vector<Entity> entities;



	};

}