#include "helper.h"

namespace cge {

	helper::helper() {

		lastFrame = glfwGetTime();

	}

	helper::~helper() {}

	GLfloat helper::getDelta() {

		GLfloat _lastFrame = lastFrame;
		lastFrame = glfwGetTime();

		return lastFrame - _lastFrame;

	}

}