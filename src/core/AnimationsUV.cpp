#include "AnimationsUV.h"

namespace cge {

	bool AnimationsUV::setCurrentAnimation(std::string & name) {
		if (name != (std::string)"__no_animation__" && currentAnimation != name && hasAnimation(name)) {
			currentAnimation = name; // copy

			currentColumn = animationsMap[name].beginX;
			currentRow = animationsMap[name].beginY;

			return true;
		}

		return false;
	}

	bool AnimationsUV::hasAnimation(std::string & name) {
		return animationsMap.find(name) != animationsMap.end();
	}

	AnimationsUV & AnimationsUV::setAnimation(std::string & name, int _beginX, int _beginY, int _endX, int _endY, float _timePerCell) {
		animationsMap[name] = impl::AnimationsUV_AnimationDetails(_beginX, _beginY, _endX, _endY, _timePerCell);

		if (currentAnimation == std::string("__no_animation__")) {
			setCurrentAnimation(name);
		}

		return *this;
	}

	void AnimationsUV::nextCell() {
		currentColumn += 1;

		if (currentColumn >= columns || currentColumn >= animationsMap[currentAnimation].endX) {
			currentRow += 1;

			if (currentRow >= rows || currentRow >= animationsMap[currentAnimation].endY) {
				currentColumn = animationsMap[currentAnimation].beginX;
				currentRow = animationsMap[currentAnimation].beginY;
			}
		}
	}

	void AnimationsUV::time(float delta) {
		currentTime += delta;

		if (currentTime >= animationsMap[currentAnimation].timePerCell) {
			currentTime = 0;
			nextCell();
		}
	}
}