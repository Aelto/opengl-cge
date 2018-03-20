#pragma once

#include "cge.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace GAME {

	class TextureStorage {
	public:
		TextureStorage() {
			assetsPNG = cge::ResourceManager::loadTexture("assets/assets.png", GL_TRUE, "assets");
			pointerPNG = cge::ResourceManager::loadTexture("assets/pointer.png", GL_TRUE, "pointer");
		};

		cge::Texture2D assetsPNG;
		cge::Texture2D pointerPNG;
	};

}