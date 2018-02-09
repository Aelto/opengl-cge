#include "game-instance.h"

namespace GAME {

  GameInstance::GameInstance(cge::AnimationsUV * CHARACTERS[])
    : app(1280, 900), camera(1280, 900), constants(), textureStorage(),
      player(
        glm::vec2(16, 16),
        glm::vec2(constants.tile_size, constants.tile_size),
		    &textureStorage.assetsPNG,
		    CHARACTERS[6]
      ) {
      camera.followSpeed = 6.0f;

      textManager.init(app.width, app.height);
      shaderStorage = GAME::ShaderStorage(app, camera);

      cursor = cge::SpriteAnimation(glm::vec2(0, 0), glm::vec2(constants.pointer_size), &textureStorage.pointerPNG, cge::AnimationsUV(1, 1)
		    .setAnimation(std::string("default"), 1, 1, 1, 1, 1000));

      glfwSetInputMode(app.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  };

}