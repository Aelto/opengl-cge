#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "Texture.h"
#include "../../utils/Circle.h"

namespace cge {

	class spriteBatch
	{
		public:

		spriteBatch();
		~spriteBatch();

		// props
		GLuint quadVAO;
		GLuint quadVBO;

		std::vector<uni::Circle> quads;
		std::vector<int> renderBatches;

		// methods
		void init();
		void begin();
		void end();
		void createRenderBatches();
		void render(cge::Texture2D texture);

	};

}

