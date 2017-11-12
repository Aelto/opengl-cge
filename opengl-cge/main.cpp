
#include "cge\cge.h"

#include <vector>
#include <map>
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

#include <ft2build.h>
#include FT_FREETYPE_H


struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};
std::map<GLchar, Character> Characters;
GLuint VAO, VBO;
void RenderText(cge::Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);


int main(int argc, char *argv[]) {
	
	cge::app app(1250, 900);
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
	
	cge::SpriteBatch::linkShaders(
		glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height)),
		camera.view, glm::vec3(1.0f, 1.0f, 1.0f)
	);
	cge::SpriteBatch batch;

	// load our textures
	cge::Texture2D texture_circle = cge::ResourceManager::LoadTexture("assets/circle.png", GL_TRUE, "circle");
	cge::Texture2D texture_player = cge::ResourceManager::LoadTexture("assets/player.png", GL_TRUE, "player");
	cge::Texture2D texture_checkClosed_W = cge::ResourceManager::LoadTexture("assets/checkClosed_W.png", GL_TRUE, "checkClosed_W");
	cge::Texture2D texture_tile = cge::ResourceManager::LoadTexture("assets/tileBrown_18.png", GL_TRUE, "tile");
	cge::Texture2D texture_adventurer = cge::ResourceManager::LoadTexture("assets/adven.png", GL_TRUE, "adven");


	cge::Hitbox playerBox(glm::vec2(50.0f, 50.0f), glm::vec2(0.0f, 0.0f));
	cge::Hitbox tileBox(glm::vec2(100.0f, 100.0f), glm::vec2(0.0f, 0.0f));

	cge::SpriteAnimation player(glm::vec2(50.0f, 550.0f), glm::vec2(50.0f, 50.0f), &texture_adventurer,
		cge::AnimationsUV(3, 9).setAnimation(std::string("default"), 0, 0, 6, 0, 1000));
	player.addBox(&playerBox);

	cge::Sprite obstacle(glm::vec2(525.0f, 525.0f), glm::vec2(100.0f, 100.0f), &texture_tile);
	obstacle.addBox(&tileBox);

	cge::Text textObject = textManager.newText("Hello world", 150, 150);
	

	GLfloat delta = helper.getDelta();
	while (!app.startLoop()) {

		delta = helper.getDelta();
		// helper.coutFramerate();

		camera.updateView();

		if (app.keys[GLFW_KEY_W] == true)
			player.acceleration.y += 1.0f;
		if (app.keys[GLFW_KEY_S] == true)
			player.acceleration.y -= 1.0f;
		if (app.keys[GLFW_KEY_D] == true)
			player.acceleration.x += 1.0f;
		if (app.keys[GLFW_KEY_A] == true)
			player.acceleration.x -= 1.0f;

		player.applyAcceleration(delta);
		player.applyVelocity(delta);
		player.applyFriction(0.9f);

		if (player.intersects(obstacle))
			player.resolve(obstacle);

		cgeShader.Use();
		batch.begin();

		player.batchDraw(batch);
		obstacle.batchDraw(batch);
		

		batch.end();
		batch.render();

		textObject.position.x = player.position.x;
		textObject.position.y = player.position.y + player.size.y + 15;
		textObject.render();

		player.time(delta * 1000.0f);
		
		// end of the drawing process
		app.endLoop();

	}

	return 0;

}