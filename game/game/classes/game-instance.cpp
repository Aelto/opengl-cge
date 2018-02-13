#include "game-instance.h"

namespace GAME {

  GameInstance::GameInstance(
    GAME::Constants * constants, GAME::Assets_uv * assets_uv,
    cge::App * app, cge::Camera * camera, cge::helper * helper,
    cge::TextManager * textManager, GAME::ShaderStorage * shaderStorage,
    GAME::TextureStorage * textureStorage)
    : constants(constants), assets_uv(assets_uv), app(app), camera(camera), 
      helper(helper), textManager(textManager), shaderStorage(shaderStorage),
      textureStorage(textureStorage),
      player(
        glm::vec2(16, 16),
        glm::vec2(constants->tile_size, constants->tile_size),
		    &textureStorage->assetsPNG,
		    assets_uv->CHARACTERS[6]
      ) {

    cursor = cge::SpriteAnimation(glm::vec2(0, 0), glm::vec2(constants->pointer_size), &textureStorage->pointerPNG, cge::AnimationsUV(1, 1)
      .setAnimation(std::string("default"), 1, 1, 1, 1, 1000));

    glfwSetInputMode(app->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  };

  void GameInstance::drawCursor() {
    cursor.position.x = app->mousePosition.x + camera->Position.x;
    cursor.position.y = app->height - app->mousePosition.y + camera->Position.y - constants->pointer_size;
    cursor.batchDraw(batchRenderer);
  }

  void GameInstance::init() {
    // player.position.x = app->width / 2;
    // player.position.y = app->height / 2;
    player.movespeed = 100.0f;

    camera->followSpeed = 6.0f;
    camera->followedPosition = &player.position;

    delta = helper->getDelta();
  }

  void GameInstance::playerControls() {
    if (app->keys[GLFW_KEY_W])
			player.acceleration.y += constants->hero_speed;
		if (app->keys[GLFW_KEY_A])
			player.acceleration.x -= constants->hero_speed;
		if (app->keys[GLFW_KEY_D])
			player.acceleration.x += constants->hero_speed;
		if (app->keys[GLFW_KEY_S])
			player.acceleration.y -= constants->hero_speed;
  }

  void GameInstance::play() {
    init();

    while (!app->startLoop()) {
      delta = helper->getDelta();
      // helper->coutFramerate();
      
      camera->runFollow(delta);
		  camera->updateView();

      playerControls();
      player.applyFriction(0.9f);

      player.mainBehavior(delta);

      batchRenderer.begin();

        drawCursor();
        player.batchDraw(batchRenderer);

      shaderStorage->spritebatchShader.use();
		  shaderStorage->spritebatchShader.setMatrix4("view", camera->view);
      batchRenderer.end();
      batchRenderer.render();


      spriteRenderer.begin();

      player.draw(spriteRenderer);

      shaderStorage->spriterendererShader.use();
		  shaderStorage->spriterendererShader.setMatrix4("view", camera->view);
      spriteRenderer.end();
      spriteRenderer.render(shaderStorage->spriterendererShader, *camera);

      app->endLoop();
    }
  }

}