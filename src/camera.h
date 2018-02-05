#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace cge {
	class Camera {
	public:
    glm::vec3 Position, Velocity, Front, Up;
		GLfloat Rotation, MovementSpeed;
		GLuint Width, Height;

		glm::mat4 view;

		glm::vec2 * followedPosition;
		glm::vec2 anchor;
		GLfloat followSpeed;

		Camera(GLuint width, GLuint height)
      : Position(0.0f, 0.0f, 0.0f), Velocity(0.0f, 0.0f, 0.0f), Front(0.0f, 0.0f, -1.0f), Up(0.0f, 1.0f, 0.0f), MovementSpeed(1.0f), Rotation(0.0f), Width(width), Height(height) {
      view = glm::lookAt(Position, Position + Front, Up);

      followedPosition = nullptr;
      anchor = glm::vec2(0.5, 0.5);
      followSpeed = 1.0f;
    }

		~Camera() {}

		void updateView() {
      view = glm::lookAt(Position, Position + Front, Up);
      //view = glm::rotate(glm::lookAt(Position, Position + Front, Up), 0.0f, glm::vec<3, float>(0.0f, 0.0f, 1.0f));
    }

		void runFollow(GLfloat delta) {
      if (followedPosition != nullptr) {
        Position.x += (followedPosition->x - Position.x - Width * anchor.x) * followSpeed * delta;
        Position.y += (followedPosition->y - Position.y - Height * anchor.y) * followSpeed * delta;
      }
    }

		float getAbsolutePositionX(float in){
      return in + Position.x;
    }
    
		float getAbsolutePositionY(float in){
      return in + Position.y;
    }
	};
}