#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include "../cge/core/Texture.h"
#include "../cge/core/Shader.h"
#include "../cge/core/SpriteBatch.h"

namespace wip {

	class RenderObject {
		RenderObject();

		/// props
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;

		glm::vec2 size;

		glm::vec3 color;

		GLfloat rotate;

		cge::Texture2D * texture;

		/// methods
		void draw(cge::SpriteBatch & spriteBatch);

		glm::vec2 distanceTo(glm::vec2 pos);

		bool intersects(RenderObject & obj);

		void calculateGravity(RenderObject & planet);

		void applyAcceleration(GLfloat delta);
		void applyVelocity(GLfloat delta);

	};

}