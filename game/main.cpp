#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cge.h"

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>


#include "game/utils/assets-uv.h"
#include "game/utils/constants.h"

#include "game/classes/entities/Creature.h"
#include "game/classes/entities/Entity.h"
#include "game/utils/ShaderStorage.h"
#include "game/utils/TextureStorage.h"
#include "game/classes/game-instance.h"

int main(int argc, char *argv[]) {
	GAME::Constants constants;
	GAME::Assets_uv assets_uv;
	
	cge::App * app = cge::App::getInstance(1280, 900);
	app->open(4, 3, "Opengl game");

	cge::Camera * camera = cge::Camera::getInstance(app->width, app->height);

	cge::helper * helper = cge::helper::getInstance();
	cge::TextManager * textManager = cge::TextManager::getInstance();
	textManager->init(app->width, app->height);

	GAME::ShaderStorage shaderStorage(*app, *camera);
	GAME::TextureStorage textureStorage;

	GAME::GameInstance gameInstance(&constants, &assets_uv, app, camera, helper, textManager, &shaderStorage, &textureStorage);
	gameInstance.play();

	return 0;
}