
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


	srand(glfwGetTime());

	std::vector<uni::Star> galaxy;
	galaxy.resize(100000);
	for (int i = 0; i < galaxy.size(); i++)
		galaxy[i] = uni::Star(glm::vec2(rand() % app.width + 0.5f, rand() % app.height + 0.5f), glm::vec2(1.0f, 1.0f), &circleTexture);

	std::vector<cge::RenderObject> planets;
	planets.resize(3);
	planets[0] = cge::RenderObject(glm::vec2(app.width / 2, 350), glm::vec2(20.0f, 20.0f), &circleTexture);
	planets[1] = cge::RenderObject(glm::vec2(app.width / 2, 500), glm::vec2(40.0f, 40.0f), &circleTexture);
	planets[2] = cge::RenderObject(glm::vec2(app.width / 2, 650), glm::vec2(20.0f, 20.0f), &circleTexture);
		

	
	

	cge::SpriteBatch batch;
	GLfloat delta = helper.getDelta();
	while ( !app.shouldClose() ) {

		std::cout << 1 / helper.getDelta() << '\n';
		delta = helper.getDelta();

		// beginning of the drawing process
		app.startLoop();
		cgeShader.Use(); 
		batch.begin();

		planets[0].velocity.x = 1.0f;
	

		glm::vec2 distance;
		for (cge::RenderObject & planet : planets) {

			for (uni::Star & star : galaxy) {

				distance.x = star.position.x - planet.position.x;
				distance.y = star.position.y - planet.position.y;


				
				if (distance.x * distance.x + distance.y * distance.y <= (planet.size.x / 2) * (planet.size.x / 2)) {
					star.velocity.x += distance.x * 0.1f;
					star.velocity.y += distance.y * 0.1f;
				}
					

			}

			planet.applyAcceleration(delta);
			planet.applyVelocity(delta);
			planet.batchDraw(batch);
		}


		static float frictionFactor = (1 - delta) * 0.9;
		for (uni::Star & star : galaxy) {

			star.velocity *= frictionFactor;

			star.goToOrigin(0.1f);
			star.applyAcceleration(delta);
			star.applyVelocity(delta);
			star.batchDraw(batch);
		}
			

		batch.end();
		batch.render();

		camera.updateView();

		// end of the drawing process
		app.endLoop();

	}

	return 0;

}