#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace cge {
	class Camera {
	private:
		Camera() {};
		Camera(GLuint width, GLuint height);

	public:
		~Camera();

		static Camera * instance;

		glm::vec3 Position, Velocity, Front, Up;
		GLfloat Rotation, MovementSpeed;
		GLuint Width, Height;

		glm::mat4 view;

		glm::vec2 * followedPosition;
		glm::vec2 anchor;
		GLfloat followSpeed;

		static Camera * getInstance(GLuint width, GLuint height);
		void updateView();
		void runFollow(GLfloat delta);
		float getAbsolutePositionX(float in);
		float getAbsolutePositionY(float in);
	};
}