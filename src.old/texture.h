#pragma once


#include <GL/glew.h>

namespace cge {

	class Texture2D {
	public:
		GLuint ID;
		GLuint width, height;
		GLuint internalFormat;
		GLuint imageFormat;
		GLuint wrap_s;
		GLuint wrap_t;
		GLuint filterMin;
		GLuint filterMax;

		Texture2D() 
		  : width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR) {
      glGenTextures(1, &ID);
    }

		void generate(GLuint width, GLuint height, unsigned char* data) {
      this->width = width;
      this->height = height;
      
      // create Texture
      glBindTexture(GL_TEXTURE_2D, this->ID);
      glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);

      // set Texture wrap and filter modes
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, /*this->Filter_Max*/GL_NEAREST);

      glBindTexture(GL_TEXTURE_2D, 0);
    }
    
		void bind() const {
      glBindTexture(GL_TEXTURE_2D, this->ID);
    }
	};

}