
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


int main( int argc, char *argv[] ) {

	cge::helper helper;

	cge::app app( 1250, 900 );
	app.open(4, 3, "opengl engine");

	// define the projection mat4
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	
	

	cge::Camera camera( app.width, app.height );

	// load and compile our shaders
	cge::Shader cgeShader = cge::ResourceManager::LoadShader( "shaders/cge.vs", "shaders/cge.frag", nullptr, "cge" );

	cgeShader.Use();
	cgeShader.SetMatrix4( "projection", projection );
	cgeShader.SetMatrix4("model", model);

	// load our texture
	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture( "assets/circle.png", GL_TRUE, "circle" );
	cge::Texture2D chestTexture = cge::ResourceManager::LoadTexture( "assets/chestClosed_W.png", GL_TRUE, "chest" );


	cge::SpriteBatch batch;

	GLfloat delta = helper.getDelta();

	glm::vec2 size(100.0f, 100.0f);
	glm::vec3 color(1.0f, 1.0f, 1.0f);
	glm::vec2 position(0.0f, 0.0f);

	cge::RenderObject circle(glm::vec2(0.0f, 0.0f), glm::vec2(50.0f, 50.0f), &circleTexture);
	cge::RenderObject circle_2(glm::vec2(200.0f, 200.0f), glm::vec2(20.0f, 20.0f), &circleTexture);

	cgeShader.SetVector3f("spriteColor", color);
	cgeShader.SetMatrix4("view", camera.view);

	while ( !app.shouldClose() ) {

		// std::cout << 1 / helper.getDelta() << '\n';
		delta = helper.getDelta();

		// beginning of the drawing process
		app.startLoop();
		cgeShader.Use(); 
		batch.begin();

		circle.batchDraw(batch);
		circle_2.batchDraw(batch);

		batch.end();
		batch.render();

		camera.updateView();

		// end of the drawing process
		app.endLoop();

	}

	return 0;

}