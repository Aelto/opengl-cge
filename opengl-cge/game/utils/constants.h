#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

namespace GAME {
	class Constants {
	public:
		Constants() {
			hero_speed = 60.0f;
			tile_size = 128;
		};

		float hero_speed;
		int tile_size;
	};
}