#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include "../cge/game/Sprite.h"

namespace uni {

	class Star : public cge::Sprite {
	public:
		Star();
		Star(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture);

		/// props
		glm::vec2 origin;

		/// methods
		void goToOrigin(float factor);
	};

}


