
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

#include "utils\Star.h"


int main( int argc, char *argv[] ) {

	cge::helper helper;

	cge::app app( 1250, 900 );
	app.open(4, 3, "opengl engine");
	
	cge::Camera camera( app.width, app.height );

	// load and compile our shaders
	cge::Shader cgeShader = cge::ResourceManager::LoadShader( "shaders/cge.vs", "shaders/cge.frag", nullptr, "cge" );
	cgeShader.Use();
	cgeShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height)));
	cgeShader.SetMatrix4("view", camera.view);
	cgeShader.SetVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));

	// load our texture
	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture( "assets/circle.png", GL_TRUE, "circle" );
	cge::Texture2D chestTexture = cge::ResourceManager::LoadTexture( "assets/chestClosed_W.png", GL_TRUE, "chest" );
	
	

	cge::SpriteBatch batch;
	GLfloat delta = helper.getDelta();
	while ( !app.startLoop() ) {

		delta = helper.getDelta();
		helper.coutFramerate();

		camera.updateView();

		cgeShader.Use(); 
		batch.begin();

		

		batch.end();
		batch.render();

		

		// end of the drawing process
		app.endLoop();

	}

	return 0;

}