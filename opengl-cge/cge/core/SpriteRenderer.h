#pragma once

#include "Shader.h"
#include "SpriteBatch.h"
#include "camera.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include <unordered_map>
#include <vector>

namespace cge {

	class Quad {
	public:
		Quad(GLfloat x, GLfloat y, GLfloat _width, GLfloat _height, GLuint _textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx,
			GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy,
			GLfloat bottomRightUVy, GLfloat bottomLeftUVy, GLfloat _rotate);

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomRight;
		Vertex bottomLeft;

		GLuint textureID;
		GLfloat rotate;
		GLfloat width;
		GLfloat height;
		GLfloat x;
		GLfloat y;
	};

	class SpriteRenderer {
	public:
		SpriteRenderer();

		void draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy, GLfloat rotate);

		void begin();

		void end();

		void render(Shader & shader, Camera & camera);

		std::vector<Quad> quads;

		GLuint quadVAO;

		GLuint quadVBO;

		GLuint quadIBO;

	};

}