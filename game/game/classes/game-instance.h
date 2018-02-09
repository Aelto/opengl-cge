#pragma once

#include "cge.h"
#include "../utils/ShaderStorage.h"
#include "../utils/TextureStorage.h"
#include "../utils/constants.h"
#include "./entities/Player.h"

namespace GAME {

  class GameInstance {
    public:

    cge::App app;
    cge::Camera camera;
    cge::helper helper;
    cge::TextManager textManager;

    GAME::ShaderStorage shaderStorage;
    GAME::TextureStorage textureStorage;
    GAME::Constants constants;

    cge::SpriteAnimation cursor;
    GAME::Player player;

    GameInstance(cge::AnimationsUV * CHARACTERS[12]);
  };

}