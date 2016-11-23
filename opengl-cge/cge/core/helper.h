#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace cge {
	class helper
	{
		public:
		helper();
		~helper();

		/// props
		double lastFrame;

		/// methods
		GLfloat getDelta();
	};
}
