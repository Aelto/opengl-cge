#pragma once

#include <GL/glew.h>

#include "vertex.h"

namespace cge {

  class Glyph {
	public:
		Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID) {
      // uses the top left corner as anchor

      topLeft.x = x;
      topLeft.y = y;
      topLeft.uvX = 0.0f;
      topLeft.uvY = 1.0f;

      topRight.x = x + width;
      topRight.y = y;
      topRight.uvX = 1.0f;
      topRight.uvY = 1.0f;

      bottomLeft.x = x;
      bottomLeft.y = y + height;
      bottomLeft.uvX = 0.0f;
      bottomLeft.uvY = 0.0f;

      bottomRight.x = x + width;
      bottomRight.y = y + height;
      bottomRight.uvX = 1.0f;
      bottomRight.uvY = 0.0f;

      textureID = _textureID;
    }

		Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID, bool inverted) {
      topLeft.x = x;
      topLeft.y = y;
      topLeft.uvX = 1.0f;
      topLeft.uvY = 0.0f;

      topRight.x = x + width;
      topRight.y = y;
      topRight.uvX = 0.0f;
      topRight.uvY = 0.0f;

      bottomLeft.x = x;
      bottomLeft.y = y + height;
      bottomLeft.uvX = 1.0f;
      bottomLeft.uvY = 1.0f;

      bottomRight.x = x + width;
      bottomRight.y = y + height;
      bottomRight.uvX = 0.0f;
      bottomRight.uvY = 1.0f;

      textureID = _textureID;
    }

		Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy) {
      // uses the top left corner as anchor

      topLeft.x = x;
      topLeft.y = y;
      topLeft.uvX = topLeftUVx;
      topLeft.uvY = topLeftUVy;

      topRight.x = x + width;
      topRight.y = y;
      topRight.uvX = topRightUVx;
      topRight.uvY = topRightUVy;

      bottomLeft.x = x;
      bottomLeft.y = y + height;
      bottomLeft.uvX = bottomLeftUVx;
      bottomLeft.uvY = bottomLeftUVy;

      bottomRight.x = x + width;
      bottomRight.y = y + height;
      bottomRight.uvX = bottomRightUVx;
      bottomRight.uvY = bottomRightUVy;

      textureID = _textureID;
    }

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomRight;
		Vertex bottomLeft;

		GLuint textureID;
	};

}