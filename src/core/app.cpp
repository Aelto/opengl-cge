#include "app.h"

#include <iostream>

namespace cge {

	App::App(GLuint _width, GLuint _height)
		: width(_width), height(_height) {

		for (auto i = 0; i < MAX_KEYS; i++)
			keys[i] = false;

	}

	App::~App() {
		App::currentApp = nullptr;

		glfwTerminate();
	}

	App * App::getInstance() {
		return App::getInstance(1280, 920);
	}

	App * App::getInstance(GLuint width, GLuint height) {
		if (App::currentApp == nullptr)
			App::currentApp = new App(width, height);

		return App::currentApp;
	}

	void App::open(int GL_major, int GL_minor, const char * name) {

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_minor);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		App::currentApp = this;
		glfwSetKeyCallback(window, App::keyCallback_dispatch);
		glfwSetCursorPosCallback(window, App::mouseCallback_dispatch);

		glewExperimental = GL_TRUE;
		const GLenum glewState = glewInit();
		if (glewState != GLEW_OK) {
			std::cout << "Glew error" << glewGetErrorString(glewState) << std::endl;
		}
		
		GLenum glErrors = glGetError(); // get any errors
		if (glErrors != GL_NO_ERROR) {
			std::cout << "OpenGL error" << std::endl;
		}

		// OpenGL configuration
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	App * App::currentApp;

	void App::keyCallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mode) {

		if (App::currentApp)
			App::currentApp->keyCallback(window, key, scancode, action, mode);

	}

	void App::mouseCallback_dispatch(GLFWwindow * window, double xpos, double ypos) {
	
		if (App::currentApp)
			App::currentApp->mouseCallback(window, xpos, ypos);

	}

	void App::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS)
				keys[key] = true;
			else if (action == GLFW_RELEASE)
				keys[key] = false;
		}

	}

	void App::mouseCallback(GLFWwindow * window, double xpos, double ypos) {
		mousePosition.x = xpos;
		mousePosition.y = ypos;
	}

	int App::shouldClose() {

		return glfwWindowShouldClose(window);

	}

	int App::startLoop() {

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return shouldClose();

	}

	void App::endLoop() {

		glfwSwapBuffers(window);
		
		if (keys[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(window, GL_TRUE);

	}

}

