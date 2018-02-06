#pragma once

namespace cge {

  /**
   * Used to store where an animations begins/ends in a AnimationsUV class
   */
  class AnimationDetails {
  public:
    int beginX;

    int beginY;

    int endX;

    int endY;

    float timePerCell;

    AnimationDetails(int _beginX, int _beginY, int _endX, int _endY, float _timePerCell)
      : beginX(_beginX), beginY(_beginY), endX(_endX), endY(_endY), timePerCell(_timePerCell) {};

    // copy  constructor
    AnimationDetails(const AnimationDetails & obj)
      : beginX(obj.beginX), beginY(obj.beginY), endX(obj.endX), endY(obj.endY), timePerCell(obj.timePerCell) {};

    AnimationDetails()
      : beginX(0), beginY(0), endX(0), endY(0), timePerCell(0.0f) {};
  };

}