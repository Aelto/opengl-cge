#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include "glm/gtc/matrix_transform.hpp"


#include "../cge/cge.h"

namespace uni {

	class Circle {
		public:
		Circle(float _radius, glm::vec2 position, cge::Texture2D * _texture, glm::vec3 _color);
		
		// props
		float radius;
		float mass;

		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;

		glm::vec3 color;

		GLfloat rotate;

		cge::Texture2D * texture;

		// methods
		void setRadius( float radius );
		void updateRadius( float delta );

		void draw( cge::Shader & spriteShader, cge::Camera & camera, GLuint quadVAO );

		glm::vec2 distanceTo( glm::vec2 pos );

		bool intersects( Circle obj );

		void calculateGravity( uni::Circle & planet );

		void applyAcceleration( GLfloat delta );
		void applyVelocity( GLfloat delta );
	};
}
