#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace cge {

	Camera * Camera::instance = nullptr;

	Camera::Camera(GLuint width, GLuint height)
		: Position(0.0f, 0.0f, 0.0f), Velocity(0.0f, 0.0f, 0.0f), Front(0.0f, 0.0f, -1.0f), Up(0.0f, 1.0f, 0.0f), MovementSpeed(1.0f), Rotation(0.0f), Width(width), Height(height) {
		view = glm::lookAt(Position, Position + Front, Up);

		followedPosition = nullptr;
		anchor = glm::vec2(0.5, 0.5);
		followSpeed = 1.0f;
	}

	cge::Camera::~Camera() {}

	Camera * Camera::getInstance(GLuint width, GLuint height) {
		if (Camera::instance == nullptr)
			Camera::instance = new Camera(width, height);

		return Camera::instance;
	}

	void Camera::updateView() {

		view = glm::lookAt(Position, Position + Front, Up);
		//view = glm::rotate(glm::lookAt(Position, Position + Front, Up), 0.0f, glm::vec<3, float>(0.0f, 0.0f, 1.0f));

	}

	void Camera::runFollow(GLfloat delta) {

		if (followedPosition != nullptr) {
			Position.x += (followedPosition->x - Position.x - Width * anchor.x) * followSpeed * delta;
			Position.y += (followedPosition->y - Position.y - Height * anchor.y) * followSpeed * delta;
		}

	}

	float Camera::getAbsolutePositionX(float in) {
		return in + Position.x;
	}

	float Camera::getAbsolutePositionY(float in) {
		return in + Position.y;
	}

}
