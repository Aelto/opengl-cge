
#include "cge\cge.h"
#include "utils\Circle.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"


int main(int argc, char *argv[]) {

	cge::helper helper;

	cge::app app(1250, 900);
	app.open(4, 3, "opengl engine");
	
	cge::Camera camera(app.width, app.height);

	// load and compile our shaders
	cge::Shader cgeShader = cge::ResourceManager::LoadShader("./shaders/cge.vs", "./shaders/cge.frag", nullptr, "cge");
	cgeShader.Use();
	cgeShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height)));
	cgeShader.SetMatrix4("view", camera.view);
	cgeShader.SetVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));

	
	cge::SpriteBatch::linkShaders(
		glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height)),
		camera.view, glm::vec3(1.0f, 1.0f, 1.0f)
	);
	cge::SpriteBatch batch;

	// load our texture
	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture("assets/circle.png", GL_TRUE, "circle");
	cge::Texture2D playerTexture = cge::ResourceManager::LoadTexture("assets/player.png", GL_TRUE, "player");
	cge::Texture2D tileTexture = cge::ResourceManager::LoadTexture("assets/tileBrown_18.png", GL_TRUE, "tile");

	cge::Hitbox playerBox(glm::vec2(50.0f, 50.0f), glm::vec2(0.0f, 0.0f));
	cge::Hitbox tileBox(glm::vec2(100.0f, 100.0f), glm::vec2(0.0f, 0.0f));

	cge::RenderObject player(glm::vec2(450.0f, 450.0f), glm::vec2(50.0f, 50.0f), &playerTexture);
	player.addBox(&playerBox);

	cge::RenderObject obstacle(glm::vec2(525.0f, 525.0f), glm::vec2(100.0f, 100.0f), &tileTexture);
	obstacle.addBox(&tileBox);

	
	
	GLfloat delta = helper.getDelta();
	while (!app.startLoop()) {

		delta = helper.getDelta();
		//helper.coutFramerate();

		camera.updateView();

		if (app.keys[GLFW_KEY_W] == true)
			player.acceleration.y += 0.1f;
		if (app.keys[GLFW_KEY_S] == true)
			player.acceleration.y -= 0.1f;
		if (app.keys[GLFW_KEY_D] == true)
			player.acceleration.x += 0.9f;
		if (app.keys[GLFW_KEY_A] == true)
			player.acceleration.x -= 0.1f;

		player.applyAcceleration(delta);
		player.applyVelocity(delta);
		player.applyFriction(0.9);

		if (player.intersects(obstacle))
			player.position.x = 100;

		cgeShader.Use();//batch.shader.Use(); 
		batch.begin();

		player.batchDraw(batch);
		obstacle.batchDraw(batch);
		

		batch.end();
		batch.render();

		
		// end of the drawing process
		app.endLoop();

	}

	return 0;

}