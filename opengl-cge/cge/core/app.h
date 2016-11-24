#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace cge {
	class app
	{
		public:
		app( GLuint _width, GLuint _height );
		~app();

		/// props
		GLuint width;
		GLuint height;

		GLboolean keys[ 1024 ];

		GLFWwindow * window;

		static app * currentApp;
		static void keyCallback_dispatch( GLFWwindow* window, int key, int scancode, int action, int mode );
		void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mode );

		/// methods
		void open( int GL_major, int GL_minor, const char * name );

		int shouldClose();
		int startLoop();
		void endLoop();

	};

	
}

