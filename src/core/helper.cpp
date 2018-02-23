#include "helper.h"

#include <iostream>

namespace cge {

	helper::helper() {

		lastFrame = GLfloat(glfwGetTime());

	}

	helper::~helper() {}

	GLfloat helper::getDelta() {

		// use delta as a temporary value holder
		delta = lastFrame;

		// this way lastFrame is already set to the current frame time
		// four our next call
		lastFrame = GLfloat(glfwGetTime());

		// so here delta is actually lastFrame and lastFrame holds the current frame time
		delta = lastFrame - delta;

		return delta;

	}

	helper * helper::instance = nullptr; 

	helper * helper::getInstance() {
		if (helper::instance == nullptr)
			helper::instance = new helper();

		return helper::instance;
	}

	void helper::coutFramerate() {

		std::cout << "fps: " << 1 / delta << std::endl;

	}

}