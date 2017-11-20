#include "Hitbox.h"

#include <iostream>

namespace cge {

	Hitbox::Hitbox(glm::vec2 customSize, glm::vec2 customPosition)
		: size(customSize), position(customPosition)
	{}

	bool Hitbox::intersects(
		Hitbox * obj,
		const glm::vec2 & obj1_position, 
		const glm::vec2 & obj2_position,
		const glm::vec2 & obj1_size,
		const glm::vec2 & obj2_size) {

			int obj_1_left = obj1_position.x + obj1_size.x * position.x - (obj1_size.x * size.x / 2);
			int obj_2_left = obj2_position.x + obj2_size.x * obj->position.x - (obj2_size.x * obj->size.x / 2);

			int obj_1_right = obj_1_left + obj1_size.x * size.x;
			int obj_2_right = obj_2_left + obj2_size.x * obj->size.x;

			int obj_1_bottom = obj1_position.y + obj1_size.y * position.y - (obj1_size.y * size.y / 2);
			int obj_2_bottom = obj2_position.y + obj2_size.y * obj->position.y - (obj2_size.y * obj->size.y / 2);

			int obj_1_top = obj_1_bottom + obj1_size.y * size.y;
			int obj_2_top = obj_2_bottom + obj2_size.y * obj->size.y;

			return !(
				obj_1_left > obj_2_right ||
				obj_1_right < obj_2_left ||
				obj_1_top < obj_2_bottom ||
				obj_1_bottom > obj_2_top
			);
	}

	void Hitbox::resolve(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position) {

		// TODO: create a real resolve
		obj1_position += glm::vec2(
			((obj1_position.x + position.x + size.x / 2) - (obj2_position.x - obj->position.x + obj->size.x / 2)) * 0.1f,
			((obj1_position.y + position.y + size.y / 2) - (obj2_position.y - obj->position.y + obj->size.y / 2)) * 0.1f
		);

	}

}


