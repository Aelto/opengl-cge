#include "app.h"

#include <iostream>

namespace cge {

	app::app(GLuint _width, GLuint _height)
		: width(_width), height(_height) {

		window = nullptr;

	}


	app::~app() {
		app::currentApp = nullptr;

		glfwTerminate();
	}


	void app::open(int GL_major, int GL_minor, const char * name) {

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_minor);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		app::currentApp = this;
		glfwSetKeyCallback(window, app::keyCallback_dispatch);

		glewExperimental = GL_TRUE;
		glewInit();
		glGetError(); // get any errors

		// OpenGL configuration
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	app * app::currentApp;

	void app::keyCallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mode) {

		if (app::currentApp)
			app::currentApp->keyCallback(window, key, scancode, action, mode);

	}

	void app::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS)
				keys[key] = true;
			else if (action == GLFW_RELEASE)
				keys[key] = false;
		}

	}

	int app::shouldClose() {

		return glfwWindowShouldClose(window);

	}

	int app::startLoop() {

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return shouldClose();

	}

	void app::endLoop() {

		glfwSwapBuffers(window);

		if (keys[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(window, GL_TRUE);

	}

}

