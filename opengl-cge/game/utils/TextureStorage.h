#pragma once

#include "../../cge/cge.h"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

namespace GAME {

	class TextureStorage {
	public:
		TextureStorage() {
			assetsPNG = cge::ResourceManager::LoadTexture("assets/assets.png", GL_TRUE, "assets");
		};

		cge::Texture2D assetsPNG;
	};

}