#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "cge.h"
#include "./utils/constants.h"
#include "./classes/chunk/chunk.h"
#include "./classes/player/player.h"

int main(int argc, char *argv[]) {
	cge::App * app = cge::App::getInstance(1280, 900)
		->hideCursor()
		->open(4, 3, "Opengl game");

	cge::Camera * camera = cge::Camera::getInstance(app->width, app->height);

	cge::helper * helper = cge::helper::getInstance();
	cge::TextManager * textManager = cge::TextManager::getInstance()
		->init(app->width, app->height);

	cge::SpriteBatch batch;

	cge::Texture2D spritesheet = cge::ResourceManager::loadTexture("assets/roguelikeSheet.png", GL_TRUE, "roguelike");
	cge::Texture2D characterSheet = cge::ResourceManager::loadTexture("assets/sokoban_tilesheet.png", GL_TRUE, "sokoban");
	cge::Texture2D pointerTexture = cge::ResourceManager::loadTexture("assets/pointer.png", GL_TRUE, "pointer");

	cge::SpriteAnimation cursor(glm::vec2(0, 0), glm::vec2(POINTER_SIZE), &pointerTexture, cge::AnimationsUV(1, 1)
      .setAnimation(std::string("default"), 1, 1, 1, 1, 1000));

	
	std::vector<game::Chunk> chunks;
	for (auto x = 0; x < 2; x++) {
		for (auto y = 0; y < 2; y++) {
			chunks.emplace_back(16, spritesheet, x * 16, y * 16);
		}
	}

	game::Player player(
		glm::vec2(0, 0),
		glm::vec2(TILE_SIZE, TILE_SIZE),
		&characterSheet,
		cge::AnimationsUV(8, 13)
			.setAnimation(std::string("default"), 0, 5, 0, 5, 1)
			.setAnimation(std::string("run_top"), 0, 5, 2, 5, 0.25)
			.setAnimation(std::string("run_bottom"), 3, 5, 5, 5, 0.25)
			.setAnimation(std::string("run_right"), 0, 7, 2, 7, 0.25)
			.setAnimation(std::string("run_left"), 3, 7, 5, 7, 0.25)
	);

	glfwSetInputMode(app->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	player.movespeed = 25.0f;
	camera->followSpeed = 6.0f;
	camera->followedPosition = &player.position;

	cge::Shader spritebatchShader = cge::ResourceManager::loadShader(
		"shaders/spritebatch.vs",
		"shaders/spritebatch.frag",
		nullptr, "spritebatch");
	spritebatchShader.use();

	spritebatchShader.setMatrix4(
		"projection",
		glm::ortho(0.0f, static_cast<GLfloat>(app->width),
			0.0f,
			static_cast<GLfloat>(app->height)));

	spritebatchShader.setMatrix4("view", camera->view);
	spritebatchShader.setVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));

	GLfloat delta = helper->getDelta();
	while (!app->startLoop()) {
		delta = helper->getDelta();

		camera->runFollow(delta);
		camera->updateView();

		if (app->keys[GLFW_KEY_W])
			player.acceleration.y += 1.0f;
		if (app->keys[GLFW_KEY_A])
			player.acceleration.x -= 1.0f;
		if (app->keys[GLFW_KEY_D])
			player.acceleration.x += 1.0f;
		if (app->keys[GLFW_KEY_S])
			player.acceleration.y -= 1.0f;

		player.applyFriction(0.9f);
		player.mainBehavior(delta);
		player.handleAnimations(delta);

		batch.begin();

		for (auto & chunk : chunks)
			for (auto & tile : chunk.tiles)
				tile.drawBatch(batch);

		player.drawBatch(batch);

		cursor.position.x = app->mousePosition.x + camera->Position.x;
    cursor.position.y = app->height - app->mousePosition.y + camera->Position.y - POINTER_SIZE;
    cursor.drawBatch(batch);

		spritebatchShader.use();
		spritebatchShader.setMatrix4("view", camera->view);
		batch.end();
		batch.render();


		app->endLoop();
	}

	return 0;
}