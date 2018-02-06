#pragma once

#include <unordered_map>
#include <string>

#include "spritesheet-uv.h"
#include "animation-details.h"

namespace cge {



	class AnimationsUV : public SpriteSheetUV {
	public:

		std::unordered_map<std::string, AnimationDetails> animationsMap;

		std::string currentAnimation;

		AnimationsUV() {};

		AnimationsUV(int _rows, int _columns)
			: SpriteSheetUV(_rows, _columns, -1.0f, -1) {
			currentAnimation = "__no_animation__";

			animationsMap[(std::string)"__no_animation__"] = AnimationDetails(0, 0, _columns, _rows, 1000.0f);
		};

		// // copy constructor
		// AnimationsUV(const AnimationsUV & obj)
		// 	: SpriteSheetUV(obj.rows, obj.columns, -1.0f, -1) {
		// 	currentAnimation = obj.currentAnimation;

		// 	for (auto it = obj.animationsMap.begin(); it != obj.animationsMap.end(); ++it) {
		// 		animationsMap[it->first] = it->second;
		// 	}
		// };

		/**
		 * try to change the currentAnimation value to the supplied name.
		 */
		bool setCurrentAnimation(std::string & name) {
      if (name != (std::string)"__no_animation__" && hasAnimation(name)) {
        currentAnimation = name; // copy

        currentColumn = animationsMap[name].beginX;
        currentRow = animationsMap[name].beginY;

        return true;
      }

      return false;
    }

		/**
		 * tell whether or not there is an animation whose name is equal to the supplied name.
		 */
		bool hasAnimation(std::string & name) {
      return animationsMap.find(name) != animationsMap.end();
    }

		/**
		 * add an animation to the registry
		 */
		AnimationsUV & setAnimation(std::string & name, int _beginX, int _beginY, int _endX, int _endY, float _timePerCell) {
      animationsMap[name] = AnimationDetails(_beginX, _beginY, _endX, _endY, _timePerCell);

      if (currentAnimation == std::string("__no_animation__")) {
        setCurrentAnimation(name);
      }

      return *this;
    }

		/**
		* Updates the positions to the next cell in the spritesheet
		* Comes back to zero if the last
		*/
		void nextCell() {
      currentColumn += 1;

      if (currentColumn >= columns || currentColumn >= animationsMap[currentAnimation].endX) {
        currentRow += 1;

        if (currentRow >= rows || currentRow >= animationsMap[currentAnimation].endY) {
          currentColumn = animationsMap[currentAnimation].beginX;
          currentRow = animationsMap[currentAnimation].beginY;
        }
      }
    }

		/**
		* Adds a tick to the counter,
		* automatically changes the current cell if 'currentTick >= ticksPerCell'
		*/
		void time(float delta) {
      currentTime += delta;

      if (currentTime >= animationsMap[currentAnimation].timePerCell) {
        currentTime = 0;
        nextCell();
      }
    }

	};

}