#pragma once

#include <GLFW/glfw3.h>

namespace cge {
	class helper {
	public:
		helper();
		~helper();

		/// props
		GLfloat lastFrame;
		GLfloat delta;

		/// methods
		GLfloat getDelta();

		void coutFramerate();
	};
}
