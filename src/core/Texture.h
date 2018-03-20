#pragma once


#include <GL/glew.h>

namespace cge {

	class Texture2D {
	public:
		
		GLuint ID;
		
		GLuint width;
		GLuint height;

		GLuint internalFormat;
		GLuint imageFormat;

		GLuint wrap_s;
		GLuint wrap_t;
		GLuint filterMin;
		GLuint filterMax;

		Texture2D();

		void generate(GLuint width, GLuint height, unsigned char* data);

		void bind() const;
	};
}