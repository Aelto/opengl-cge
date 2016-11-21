#include "helper.h"



cge::helper::helper()
{
	lastFrame = glfwGetTime();
}


cge::helper::~helper()
{
}

GLfloat cge::helper::getDelta() {

	GLfloat _lastFrame = lastFrame;
	lastFrame = glfwGetTime();

	return lastFrame - _lastFrame;

}
