#pragma once

#include <GL/glew.h>

namespace cge {

  class GlyphBatch {
	public:
		GlyphBatch(GLuint _textureID, GLuint _verticesNumber, GLuint _offset)
			: textureID(_textureID), verticesNumber(_verticesNumber), offset(_offset) {}

		GLuint textureID;
		GLuint verticesNumber;
		GLuint offset;
	};

}