
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

	
	cge::SpriteBatch::linkShaders(
		glm::ortho(0.0f, static_cast<GLfloat>(app.width), 0.0f, static_cast<GLfloat>(app.height)),
		camera.view, glm::vec3(1.0f, 1.0f, 1.0f)
	);
	cge::SpriteBatch batch;

	// load our texture
	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture( "assets/circle.png", GL_TRUE, "circle" );

	cge::RenderObject circle(glm::vec2(450.0f, 450.0f), glm::vec2(50.0f, 50.0f), &circleTexture);
	
	GLfloat delta = helper.getDelta();
	while ( !app.startLoop() ) {

		delta = helper.getDelta();
		helper.coutFramerate();

		camera.updateView();

		batch.shader.Use(); 
		batch.begin();

		circle.batchDraw(batch);

		batch.end();
		batch.render();

		

		// end of the drawing process
		app.endLoop();

	}

	return 0;

}