#pragma once

#include <iostream>

#include <GLFW/glfw3.h>

namespace cge {
	class helper {
	public:
		GLfloat lastFrame;
		GLfloat delta;

		helper() {
      lastFrame = GLfloat(glfwGetTime());
    }


		GLfloat getDelta(){
      // use delta as a temporary value holder
      delta = lastFrame;

      // this way lastFrame is already set to the current frame time
      // for our next call
      lastFrame = GLfloat(glfwGetTime());

      // so here delta is actually lastFrame and lastFrame holds the current frame time
      delta = lastFrame - delta;

      return delta;
    }
    
		void coutFramerate() {
      std::cout << "fps: " << 1 / delta << std::endl;
    }
	};
}