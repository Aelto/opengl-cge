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


// #include "game/utils/assets-uv.h"
#include "game/utils/constants.h"
	
GAME::Constants constants;
// GAME::Assets_uv assets_uv;

#include "cge.h"

#include "game/classes/entities/Creature.h"
#include "game/classes/entities/Entity.h"
#include "game/utils/ShaderStorage.h"
#include "game/utils/TextureStorage.h"
#include "game/classes/game-instance.h"

inline void drawCursor(cge::App & app, cge::Camera & camera, cge::SpriteAnimation & cursor, cge::SpriteBatch & batch);

int main(int argc, char *argv[]) {
	const cge::AnimationsUV CHARACTERS[12]{
		cge::AnimationsUV(16, 16)
		.setAnimation(std::string("default"), 6, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 7, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 8, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 9, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 10, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 11, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 6, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 7, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 8, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 9, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 10, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 11, 15, 16, 16, 1000)
	};

	const cge::AnimationsUV CREATURES[34]{
		cge::AnimationsUV(16, 16)
		.setAnimation(std::string("default"), 0, 10, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 10, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 10, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 10, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 10, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 5, 10, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 11, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 11, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 11, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 11, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 11, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 5, 11, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 12, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 12, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 12, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 12, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 12, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 5, 12, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 13, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 13, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 13, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 13, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 13, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 5, 13, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 5, 14, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 15, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 15, 16, 16, 1000)
	};

	const cge::AnimationsUV FLOORS[14]{
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 7, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 7, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 7, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 7, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 7, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 8, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 8, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 8, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 8, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 4, 8, 16, 16, 1000),

		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 0, 9, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 1, 9, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 2, 9, 16, 16, 1000),
		cge::AnimationsUV(16, 16)
			.setAnimation(std::string("default"), 3, 9, 16, 16, 1000)
	};

	const cge::AnimationsUV WALLS[3]{
		cge::AnimationsUV(8, 8)
		.setAnimation(std::string("default"), 0, 0, 16, 8, 1000),
		cge::AnimationsUV(16, 8)
		.setAnimation(std::string("default"), 1, 1, 16, 8, 1000),
		cge::AnimationsUV(16, 8)
		.setAnimation(std::string("default"), 2, 1, 16, 8, 1000),
	};

	cge::App app(1280, 900);
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
		CHARACTERS[6]);

	camera.followedPosition = &player.position;

	std::vector<GAME::Entity> walls;
	walls.push_back(GAME::Entity(
		glm::vec2(app.width / 2, app.height / 2),
		glm::vec2(constants.tile_size * 2, constants.tile_size * 2),
		&textureStorage.assetsPNG,
		WALLS[0]));

	GAME::Creature creature(
		glm::vec2(150, 150),
		glm::vec2(constants.tile_size, constants.tile_size),
		&textureStorage.assetsPNG,
		CREATURES[0],
		true
	);

	cge::Hitbox wallBox(glm::vec2(1.0f, 0.3f), glm::vec2(0.5f, 0.2f));
	cge::Hitbox playerBox(glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.5f));

	// auto room = GAME::Room(16, 16, 0, 0);
	// room.generate(constants, textureStorage,  wallBox);

	for (auto & wall : walls) wall.addBox(&wallBox);
	player.addBox(&playerBox);
	creature.addBox(&playerBox);

	player.movespeed = 100.0f;
	creature.movespeed = 50.0f;

	cge::SpriteBatch batch;
	cge::SpriteRenderer spriteRenderer;
	GLfloat delta = helper.getDelta();
	while (!app.startLoop()) {
		delta = helper.getDelta();
		// helper.coutFramerate();
		camera.runFollow(delta);
		camera.updateView();

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

		// room.intersects(delta, player);
		// room.intersects(delta, creature);

		player.applyFriction(0.9f);
		creature.applyFriction(0.9f);

		batch.begin();

		// room.render(batch);

		for (auto & wall : walls) 
			wall.batchDraw(batch);

		creature.batchDraw(batch);
		player.batchDraw(batch);

		creature.interactWithPlayer(player);
		drawCursor(app, camera, cursor, batch);
		
		shaderStorage.spritebatchShader.use();
		shaderStorage.spritebatchShader.setMatrix4("view", camera.view);
		batch.end();
		batch.render();


		spriteRenderer.begin();

		player.draw(spriteRenderer);


		shaderStorage.spriterendererShader.use();
		shaderStorage.spriterendererShader.setMatrix4("view", camera.view);
		spriteRenderer.end();
		spriteRenderer.render(shaderStorage.spriterendererShader, camera);

		// end of the drawing process
		app.endLoop();
	}

	return 0;

}

inline void drawCursor(cge::App & app, cge::Camera & camera, cge::SpriteAnimation & cursor, cge::SpriteBatch & batch) {
	cursor.position.x = app.mousePosition.x + camera.Position.x;
	cursor.position.y = app.height - app.mousePosition.y + camera.Position.y;
	cursor.batchDraw(batch);
}