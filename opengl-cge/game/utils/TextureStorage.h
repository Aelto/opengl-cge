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
			pointerPNG = cge::ResourceManager::LoadTexture("assets/pointer.png", GL_TRUE, "pointer");
		};

		cge::Texture2D assetsPNG;
		cge::Texture2D pointerPNG;
	};

}