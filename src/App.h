#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cge {

  class App {
	public:
    GLuint width;
		GLuint height;

		bool keys[1024];
		glm::vec2 mousePosition;
    GLFWwindow * window;

		static App * currentApp;

		App(GLuint _width, GLuint _height)
      : width(_width), height(_height) {
      window = nullptr;
    }

		~App() {
      App::currentApp = nullptr;

      glfwTerminate();
    }

		static void keyCallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mode) {
      if (App::currentApp)
        App::currentApp->keyCallback(window, key, scancode, action, mode);
    }

		static void mouseCallback_dispatch(GLFWwindow* window, double xpos, double ypos){
      if (App::currentApp)
        App::currentApp->mouseCallback(window, xpos, ypos);
    }

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

      if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
          keys[key] = true;
        else if (action == GLFW_RELEASE)
          keys[key] = false;
      }
    }

		void mouseCallback(GLFWwindow* window, double xpos, double ypos){
      mousePosition.x = xpos;
      mousePosition.y = ypos;
    }

		void open(int GL_major, int GL_minor, const char * name) {
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
      glewInit();
      glGetError(); // get any errors

      // OpenGL configuration
      glViewport(0, 0, width, height);
      glEnable(GL_CULL_FACE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

		int shouldClose(){
      return glfwWindowShouldClose(window);
    }

		int startLoop() {
      glfwPollEvents();
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      return shouldClose();
    }

		void endLoop() {
      glfwSwapBuffers(window);

      if (keys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

	};

  App * App::currentApp;

};
