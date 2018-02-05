#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include <iostream>
#include <cge.h>



int main() {
  cge::App app(1280, 900);
  app.open(4, 3, "OpenGL game");

  cge::Camera camera(app.width, app.height);
  camera.followSpeed = 6.0f;

  while (!app.startLoop()) {

    app.endLoop();
  }
  
  return 0;
}