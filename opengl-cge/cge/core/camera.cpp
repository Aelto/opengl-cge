#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

cge::Camera::Camera( GLuint width, GLuint height )
	: Position( 0.0f, 0.0f, 0.0f ), Velocity( 0.0f, 0.0f, 0.0f ), Front( 0.0f, 0.0f, -1.0f ), Up( 0.0f, 1.0f, 0.0f ), MovementSpeed( 1.0f ), Rotation( 0.0f ), Width( width ), Height( height )
{
	view = glm::lookAt( Position, Position + Front, Up );

	followedPosition = nullptr;
	anchor = glm::vec2( 0.5, 0.5 );
	followSpeed = 1.0f;
}


cge::Camera::~Camera()
{
}

void cge::Camera::updateView() {

	view = glm::lookAt( Position, Position + Front, Up );

}

void cge::Camera::runFollow() {

	if ( followedPosition != nullptr )
	{
		Position.x += ( followedPosition->x - Position.x - Width * anchor.x ) * followSpeed;
		Position.y += ( followedPosition->y - Position.y - Height * anchor.y ) * followSpeed;
	}

}