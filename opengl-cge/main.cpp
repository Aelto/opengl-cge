
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


#include "game/assets-uv.h";
#include "game/constants.h";

int main(int argc, char *argv[]) {
	
	cge::app app(1280, 900);
	app.open(4, 3, "opengl engine");
	
	cge::Camera camera(app.width, app.height);
	cge::helper helper;
	cge::TextManager textManager;
	textManager.init(app.width, app.height);

	// load and compile our shaders
	cge::Shader cgeShader = cge::ResourceManager::LoadShader("./shaders/cge.vs", "./shaders/cge.frag", nullptr, "cge");
	cgeShader.Use();
	cgeShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height)));
	cgeShader.SetMatrix4("view", camera.view);
	cgeShader.SetVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));
	
	cge::Texture2D TEXTURE = cge::ResourceManager::LoadTexture("assets/assets.png", GL_TRUE, "assets");

	cge::SpriteBatch batch;

	cge::SpriteAnimation player(
		glm::vec2(16, 16),
		glm::vec2(GAME::constants::tile_size, GAME::constants::tile_size),
		&TEXTURE,
		GAME::assets_uv::CREATURES[20]);

	std::vector<cge::SpriteAnimation> floors;
	for (auto x = 0; x < 10; x += 1)
		for (auto y = 0; y < 10; y += 1) {
			floors.push_back(
				cge::SpriteAnimation(
					glm::vec2(x * GAME::constants::tile_size, y * GAME::constants::tile_size),
					glm::vec2(GAME::constants::tile_size, GAME::constants::tile_size),
					&TEXTURE,
					GAME::assets_uv::FLOORS[5]
				)
			);
		}

	

	cge::SpriteAnimation wall(
		glm::vec2(app.width / 2, app.height / 2),
		glm::vec2(GAME::constants::tile_size * 2, GAME::constants::tile_size * 2),
		&TEXTURE,
		GAME::assets_uv::WALLS[0]);

	cge::Hitbox wallBox(glm::vec2(1.0f, 0.6f), glm::vec2(0.5f, 0.5f));
	cge::Hitbox playerBox(glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.5f));
	wall.addBox(&wallBox);
	player.addBox(&playerBox);

	GLfloat delta = helper.getDelta();
	while (!app.startLoop()) {
		delta = helper.getDelta();
		helper.coutFramerate();
		camera.updateView();

		if (app.keys[GLFW_KEY_W])
			player.acceleration.y += GAME::constants::hero_speed * delta;
		if (app.keys[GLFW_KEY_A])
			player.acceleration.x -= GAME::constants::hero_speed * delta;
		if (app.keys[GLFW_KEY_D])
			player.acceleration.x += GAME::constants::hero_speed * delta;
		if (app.keys[GLFW_KEY_S])
			player.acceleration.y -= GAME::constants::hero_speed * delta;

		player.applyAcceleration(delta);
		player.applyVelocity(delta);

		if (player.intersects(wall)) {
			player.position -= player.velocity;
			// player.resolve(wall);
		}

		player.applyFriction(0.9f);

		
			

		batch.begin();

		
		for (auto & floor : floors)
			floor.batchDraw(batch);

		wall.batchDraw(batch);
		player.batchDraw(batch);

		batch.end();
		batch.render();

		// player.time(delta * 1000.0f);

		// end of the drawing process
		app.endLoop();
	}

	return 0;

}