#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace cge {
	class Camera {
	public:
		Camera() {};
		Camera(GLuint width, GLuint height);
		~Camera();

		glm::vec3 Position, Velocity, Front, Up;
		GLfloat Rotation, MovementSpeed;
		GLuint Width, Height;

		glm::mat4 view;

		glm::vec2 * followedPosition;
		glm::vec2 anchor;
		GLfloat followSpeed;

		void updateView();
		void runFollow(GLfloat delta);
		float getAbsolutePositionX(float in);
		float getAbsolutePositionY(float in);
	};
}