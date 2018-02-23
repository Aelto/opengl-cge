#pragma once

#include <GLFW/glfw3.h>

namespace cge {
	class helper {
	private:
		helper();
	public:
		~helper();

		/// props
		GLfloat lastFrame;
		GLfloat delta;

		static helper * instance;

		/// methods
		GLfloat getDelta();
		static helper * getInstance();

		void coutFramerate();
	};
}
