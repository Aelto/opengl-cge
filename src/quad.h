#pragma once

#include <GL\glew.h>
#include "vertex.h"

namespace cge {

  class Quad {
	public:
		Quad(GLfloat x, GLfloat y, GLfloat _width, GLfloat _height, GLuint _textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx,
			GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy,
			GLfloat bottomRightUVy, GLfloat bottomLeftUVy, GLfloat _rotate): x(x), y(y) {
			// TODO: maybe optimising this to only use width and height once instead of 3 times.
			width = _width;
			height = _height;

			topLeft.x = 0;
			topLeft.y = 0;
			topLeft.uvX = topLeftUVx;
			topLeft.uvY = topLeftUVy;

			topRight.x = width;
			topRight.y = 0;
			topRight.uvX = topRightUVx;
			topRight.uvY = topRightUVy;

			bottomLeft.x = 0;
			bottomLeft.y = height;
			bottomLeft.uvX = bottomLeftUVx;
			bottomLeft.uvY = bottomLeftUVy;

			bottomRight.x = width;
			bottomRight.y = height;
			bottomRight.uvX = bottomRightUVx;
			bottomRight.uvY = bottomRightUVy;

			textureID = _textureID;
			rotate = _rotate;
		}

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

}