#pragma once

#include "../../cge/game/AnimationsUV.h"
#include "../../cge/core/ResourceManager.h"

namespace GAME {
	class Assets_uv {
	public:
		Assets_uv() {};

		const cge::AnimationsUV CHARACTERS[12]{
			cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 6, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 7, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 8, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 9, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 10, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 11, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 6, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 7, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 8, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 9, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 10, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 11, 15, 16, 16, 1000)
		};

		const cge::AnimationsUV CREATURES[34]{
			cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 10, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 10, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 10, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 10, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 10, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 5, 10, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 11, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 11, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 11, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 11, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 11, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 5, 11, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 12, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 12, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 12, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 12, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 12, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 5, 12, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 13, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 13, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 13, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 13, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 13, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 5, 13, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 5, 14, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 15, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 15, 16, 16, 1000)
		};

		const cge::AnimationsUV FLOORS[14]{
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 7, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 7, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 7, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 7, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 7, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 8, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 8, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 8, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 8, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 4, 8, 16, 16, 1000),

			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 0, 9, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 1, 9, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 2, 9, 16, 16, 1000),
			cge::AnimationsUV(16, 16)
				.setAnimation(std::string("default"), 3, 9, 16, 16, 1000)
		};

		const cge::AnimationsUV WALLS[3]{
			cge::AnimationsUV(8, 8)
			.setAnimation(std::string("default"), 0, 0, 16, 8, 1000),
			cge::AnimationsUV(16, 8)
			.setAnimation(std::string("default"), 1, 1, 16, 8, 1000),
			cge::AnimationsUV(16, 8)
			.setAnimation(std::string("default"), 2, 1, 16, 8, 1000),
		};;
	};
}