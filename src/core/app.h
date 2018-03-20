#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

namespace cge {
	class App {
	private:
		App(GLuint _width, GLuint _height);
	public:
		~App();

		GLuint width;
		GLuint height;

		static const int MAX_KEYS = 1024;
		bool keys[MAX_KEYS];
		glm::vec2 mousePosition;

		GLFWwindow * window;

		static App * currentApp;
		static void keyCallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouseCallback_dispatch(GLFWwindow* window, double xpos, double ypos);
		static App * getInstance();
		static App * getInstance(GLuint width, GLuint height);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		void open(int GL_major, int GL_minor, const char * name);

		int shouldClose();
		int startLoop();
		void endLoop();

	};


}

