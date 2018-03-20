#pragma once

#include <GLFW/glfw3.h>

namespace cge {
	class helper {
	private:
		helper();
	public:
		~helper();

		GLfloat lastFrame;
		GLfloat delta;

		static helper * instance;

		GLfloat getDelta();
		static helper * getInstance();

		void coutFramerate();
	};
}
