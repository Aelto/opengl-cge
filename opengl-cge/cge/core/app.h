#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>

#include <string>

namespace cge {
	class App {
	public:
		App(GLuint _width, GLuint _height);
		~App();

		/// props
		GLuint width;
		GLuint height;

		bool keys[1024];
		glm::vec2 mousePosition;

		GLFWwindow * window;

		static App * currentApp;
		static void keyCallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void mouseCallback_dispatch(GLFWwindow* window, double xpos, double ypos);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		/// methods
		void open(int GL_major, int GL_minor, const char * name);

		int shouldClose();
		int startLoop();
		void endLoop();

	};


}

