#pragma once

#include "cge.h"
#include "../entity/entity.h"

#include <iostream>

namespace game {

	class Player : public game::Entity {
	public:
		Player(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, cge::AnimationsUV _animationsUV);

		void handleAnimations(GLfloat delta) {

			if (velocity.x > 0 && velocity.x * velocity.x > velocity.y * velocity.y) {
				animationsUV.setCurrentAnimation(std::string("run_right"));
			}

			if (velocity.x < 0 && velocity.x * velocity.x > velocity.y * velocity.y) {
				animationsUV.setCurrentAnimation(std::string("run_left"));
			}

			if (velocity.y > 0 && velocity.y * velocity.y > velocity.x * velocity.x) {
				animationsUV.setCurrentAnimation(std::string("run_bottom"));
			}

			if (velocity.y < 0 && velocity.y * velocity.y > velocity.x * velocity.x) {
				animationsUV.setCurrentAnimation(std::string("run_top"));
			}

			animationsUV.time(delta);
		}
	};

}