#pragma once

#include "cge.h"
#include "../utils/ShaderStorage.h"
#include "../utils/TextureStorage.h"
#include "../utils/constants.h"
#include "../utils/assets-uv.h"
#include "./entities/Player.h"

namespace GAME {

  class GameInstance {
    public:

    cge::App * app;
    cge::Camera * camera;
    cge::helper * helper;
    cge::TextManager * textManager;
  
    GAME::ShaderStorage * shaderStorage;
    GAME::TextureStorage * textureStorage;
    GAME::Constants * constants;
    GAME::Assets_uv * assets_uv;

    cge::SpriteAnimation cursor;
    GAME::Player player;

    cge::SpriteBatch batchRenderer;
	  cge::SpriteRenderer spriteRenderer;

    GLfloat delta;

    GameInstance(
      GAME::Constants * constants, GAME::Assets_uv * assets_uv,
      cge::App * app, cge::Camera * camera, cge::helper * helper,
      cge::TextManager * textManager, GAME::ShaderStorage * shaderStorage,
      GAME::TextureStorage * textureStorage);

    void init();

    void drawCursor();

    void playerControls();

    void play();
  };

}