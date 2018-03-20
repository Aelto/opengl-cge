#pragma once

#include <unordered_map>
#include <string>

#include "SpriteSheetUV.h"

namespace cge {

	namespace impl {

		/**
		 * Used to store where an animations begins/ends in a AnimationsUV class
		 */
		class AnimationsUV_AnimationDetails {
		public:
			int beginX;

			int beginY;

			int endX;

			int endY;

			float timePerCell;

			AnimationsUV_AnimationDetails(int _beginX, int _beginY, int _endX, int _endY, float _timePerCell)
				: beginX(_beginX), beginY(_beginY), endX(_endX), endY(_endY), timePerCell(_timePerCell) {};

			// copy  constructor
			AnimationsUV_AnimationDetails(const AnimationsUV_AnimationDetails & obj)
				: beginX(obj.beginX), beginY(obj.beginY), endX(obj.endX), endY(obj.endY), timePerCell(obj.timePerCell) {};

			AnimationsUV_AnimationDetails()
				: beginX(0), beginY(0), endX(0), endY(0), timePerCell(0.0f) {};
		};
	}



	class AnimationsUV : public SpriteSheetUV {
	public:

		std::unordered_map<std::string, impl::AnimationsUV_AnimationDetails> animationsMap;

		std::string currentAnimation;

		AnimationsUV() {};

		AnimationsUV(int _rows, int _columns)
			: SpriteSheetUV(_rows, _columns, -1.0f, -1) {
			currentAnimation = "__no_animation__";

			animationsMap[(std::string)"__no_animation__"] = impl::AnimationsUV_AnimationDetails(0, 0, _columns, _rows, 1000.0f);
		};

		/**
		 * try to change the currentAnimation value to the supplied name.
		 */
		bool setCurrentAnimation(std::string & name);

		/**
		 * tell whether or not there is an animation whose name is equal to the supplied name.
		 */
		bool hasAnimation(std::string & name);

		/**
		 * add an animation to the registry
		 */
		AnimationsUV & setAnimation(std::string & name, int _beginX, int _beginY, int _endX, int _endY, float _timePerCell);

		/**
		* Updates the positions to the next cell in the spritesheet
		* Comes back to zero if the last
		*/
		void nextCell();

		/**
		* Adds a tick to the counter,
		* automatically changes the current cell if 'currentTick >= ticksPerCell'
		*/
		void time(float delta);

	};

}