﻿
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

#include "game/classes/Creature.h"
#include "game/utils/ShaderStorage.h"
#include "game/utils/TextureStorage.h"

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


	//cge::Texture2D TEXTURE = cge::ResourceManager::LoadTexture("assets/assets.png", GL_TRUE, "assets");

	auto player = cge::SpriteAnimation(
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

	cge::SpriteAnimation wall(
		glm::vec2(app.width / 2, app.height / 2),
		glm::vec2(constants.tile_size * 2, constants.tile_size * 2),
		&textureStorage.assetsPNG,
		assets_uv.WALLS[0]);

	GAME::Creature creature(
		glm::vec2(150, 150),
		glm::vec2(constants.tile_size, constants.tile_size),
		&textureStorage.assetsPNG,
		assets_uv.CREATURES[0]
	);

	cge::Hitbox wallBox(glm::vec2(1.0f, 0.3f), glm::vec2(0.5f, 0.2f));
	cge::Hitbox playerBox(glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.5f));
	wall.addBox(&wallBox);
	player.addBox(&playerBox);

	cge::SpriteBatch batch;
	GLfloat delta = helper.getDelta();
	while (!app.startLoop()) {
		delta = helper.getDelta();
		helper.coutFramerate();
		camera.runFollow(delta);
		camera.updateView();

		shaderStorage.defaultShader.SetMatrix4("view", camera.view);
		//cgeShader.SetMatrix4("view", camera.view);

		if (app.keys[GLFW_KEY_W])
			player.acceleration.y += constants.hero_speed * delta;
		if (app.keys[GLFW_KEY_A])
			player.acceleration.x -= constants.hero_speed * delta;
		if (app.keys[GLFW_KEY_D])
			player.acceleration.x += constants.hero_speed * delta;
		if (app.keys[GLFW_KEY_S])
			player.acceleration.y -= constants.hero_speed * delta;

		if (app.keys[GLFW_KEY_I])
			creature.inverted = !creature.inverted;

		player.applyAcceleration(delta);
		player.applyVelocity(delta);

		if (player.intersects(wall)) {
			player.acceleration *= 0;
			player.position -= player.velocity;
		}

		player.applyFriction(0.9f);

		batch.begin();


		for (auto & floor : floors)
			floor.batchDraw(batch);

		wall.batchDraw(batch);
		creature.batchDraw(batch);
		player.batchDraw(batch);


		batch.end();
		batch.render();

		// player.time(delta * 1000.0f);

		// end of the drawing process
		app.endLoop();
	}

	return 0;

}