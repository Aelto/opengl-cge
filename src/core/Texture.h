#pragma once


#include <GL/glew.h>

namespace cge {
	// Texture2D is able to store and configure a texture in OpenGL.
	// It also hosts utility functions for easy management.
	class Texture2D {
	public:
		// Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
		GLuint ID;
		// Texture image dimensions
		GLuint width, height; // Width and height of loaded image in pixels

								// Texture Format
		GLuint internalFormat; // Format of texture object
		GLuint imageFormat; // Format of loaded image

							 // Texture configuration
		GLuint wrap_s; // Wrapping mode on S axis
		GLuint wrap_t; // Wrapping mode on T axis
		GLuint filterMin; // Filtering mode if texture pixels < screen pixels
		GLuint filterMax; // Filtering mode if texture pixels > screen pixels
							 // Constructor (sets default texture modes)
		Texture2D();
		// Generates texture from image data
		void generate(GLuint width, GLuint height, unsigned char* data);
		// Binds the texture as the current active GL_TEXTURE_2D texture object
		void bind() const;
	};
}