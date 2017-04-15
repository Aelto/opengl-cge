#include "Star.h"


namespace uni {
	Star::Star()
		: Sprite()
	{
		origin = glm::vec2(position.x, position.y);
	}

	Star::Star(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture)
		: Sprite(pos, size, _texture), origin(pos)
	{
	}

	void uni::Star::goToOrigin(float factor)
	{

		acceleration.x += (origin.x - position.x) * factor;
		acceleration.y += (origin.y - position.y) * factor;

	}

}
