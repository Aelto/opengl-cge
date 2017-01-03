#include "Hitbox.h"

namespace cge {

	Hitbox::Hitbox(glm::vec2 customSize, glm::vec2 customPosition)
		: size(customSize), position(customPosition)
	{}

	bool Hitbox::intersects(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position) {

		return !(obj1_position.x + position.x			> obj2_position.x + obj->position.x + obj->size.x
			  || obj1_position.y + position.y			> obj2_position.y + obj->position.y + obj->size.y
			  || obj1_position.x + position.x + size.x	< obj2_position.x + obj->position.x
			  || obj1_position.y + position.y + size.y	< obj2_position.y + obj->position.y);

	}

	void Hitbox::resolve(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position)
	{

		// TODO: create a real resolve
		obj1_position += glm::vec2(
			((obj1_position.x + position.x + size.x / 2) - (obj2_position.x - obj->position.x + obj->size.x / 2)) * 0.1f,
			((obj1_position.y + position.y + size.y / 2) - (obj2_position.y - obj->position.y + obj->size.y / 2)) * 0.1f
		);

	}

}


