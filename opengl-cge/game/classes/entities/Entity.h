#pragma once

#include <vector>

#include "../../../cge/game/SpriteAnimation.h"
#include "../../../cge/game/AnimationsUV.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

namespace GAME {
	class Entity : public cge::SpriteAnimation {
	public:
		Entity();
		Entity(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV);

		void mainBehavior(GLfloat delta, std::vector<Entity> & collisionEntities);

		GLfloat movespeed;
	};
}



