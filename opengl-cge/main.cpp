
#include "cge\cge.h"

#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"


#include "game/utils/assets-uv.h"
#include "game/utils/constants.h"

GAME::Constants constants;
GAME::Assets_uv assets_uv;

#include "game/classes/entities/Creature.h"
#include "game/classes/entities/Entity.h"
#include "game/utils/ShaderStorage.h"
#include "game/utils/TextureStorage.h"

inline void drawCursor(cge::app & app, cge::Camera & camera, cge::SpriteAnimation & cursor, cge::SpriteBatch & batch);

/**
 * TODO: faire une classe Room, qui permettrait de render une room complète avec tout ses murs,
 * le sol, les portes
 */

int main(int argc, char *argv[]) {
	cge::app app(1280, 900);
	app.open(4, 3, "Opengl engine");

	cge::Camera camera(app.width, app.height);
	camera.followSpeed = 6.0f;

	cge::helper helper;
	cge::TextManager textManager;
	textManager.init(app.width, app.height);

	GAME::ShaderStorage shaderStorage(app, camera);
	GAME::TextureStorage textureStorage;

	glfwSetInputMode(app.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	auto cursor = cge::SpriteAnimation(glm::vec2(0, 0), glm::vec2(constants.pointer_size), &textureStorage.pointerPNG, cge::AnimationsUV(1, 1)
		.setAnimation(std::string("default"), 1, 1, 1, 1, 1000));

	auto player = GAME::Player(
		glm::vec2(16, 16),
		glm::vec2(constants.tile_size, constants.tile_size),
		&textureStorage.assetsPNG,
		assets_uv.CHARACTERS[6]);

	camera.followedPosition = &player.position;

	std::vector<cge::SpriteAnimation> floors;
	for (auto x = 0; x < 10; x += 1)
		for (auto y = 0; y < 10; y += 1) {
			floors.push_back(
				cge::SpriteAnimation(
					glm::vec2(x * constants.tile_size, y * constants.tile_size),
					glm::vec2(constants.tile_size, constants.tile_size),
					&textureStorage.assetsPNG,
					assets_uv.FLOORS[5]
				)
			);
		}

	std::vector<GAME::Entity> walls;
	walls.push_back(GAME::Entity(
		glm::vec2(app.width / 2, app.height / 2),
		glm::vec2(constants.tile_size * 2, constants.tile_size * 2),
		&textureStorage.assetsPNG,
		assets_uv.WALLS[0]));

	GAME::Creature creature(
		glm::vec2(150, 150),
		glm::vec2(constants.tile_size, constants.tile_size),
		&textureStorage.assetsPNG,
		assets_uv.CREATURES[0],
		true
	);

	cge::Hitbox wallBox(glm::vec2(1.0f, 0.3f), glm::vec2(0.5f, 0.2f));
	cge::Hitbox playerBox(glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.5f));
	for (auto & wall : walls) wall.addBox(&wallBox);
	player.addBox(&playerBox);
	creature.addBox(&playerBox);

	player.movespeed = 100.0f;
	creature.movespeed = 50.0f;

	cge::SpriteBatch batch;
	GLfloat delta = helper.getDelta();
	while (!app.startLoop()) {
		delta = helper.getDelta();
		helper.coutFramerate();
		camera.runFollow(delta);
		camera.updateView();

		shaderStorage.defaultShader.SetMatrix4("view", camera.view);

		if (app.keys[GLFW_KEY_W])
			player.acceleration.y += constants.hero_speed;
		if (app.keys[GLFW_KEY_A])
			player.acceleration.x -= constants.hero_speed;
		if (app.keys[GLFW_KEY_D])
			player.acceleration.x += constants.hero_speed;
		if (app.keys[GLFW_KEY_S])
			player.acceleration.y -= constants.hero_speed;

		if (app.keys[GLFW_KEY_I])
			player.rotate += 1.0f * delta;
		if (app.keys[GLFW_KEY_U])
			player.rotate -= 1.0f * delta;

		player.mainBehavior(delta, walls);
		creature.mainBehavior(delta, walls);

		batch.begin();

		for (auto & floor : floors)
			floor.batchDraw(batch);

		for (auto & wall : walls) 
			wall.batchDraw(batch);

		creature.batchDraw(batch);
		player.batchDraw(batch);

		creature.interactWithPlayer(player);
		drawCursor(app, camera, cursor, batch);
		batch.end();
		batch.render();

		// player.time(delta * 1000.0f);

		// end of the drawing process
		app.endLoop();
	}

	return 0;

}

inline void drawCursor(cge::app & app, cge::Camera & camera, cge::SpriteAnimation & cursor, cge::SpriteBatch & batch) {
	cursor.position.x = app.mousePosition.x + camera.Position.x;
	cursor.position.y = app.height - app.mousePosition.y + camera.Position.y;
	cursor.batchDraw(batch);
}