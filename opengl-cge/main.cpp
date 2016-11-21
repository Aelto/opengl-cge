
#include "cge\cge.h"
#include "utils\Circle.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "wip\spriteBatch.h"

//#include "wip\SpriteBatch.h"
//#include "wip\Vertex.h"


int main( int argc, char *argv[] ) {

	cge::helper helper;

	cge::app app( 1250, 900 );
	app.open(4, 3, "opengl engine");

	// define the projection mat4
	glm::mat4 projection = glm::ortho( 0.0f, static_cast<GLfloat>( app.width ), static_cast<GLfloat>( app.height ), 0.0f);
	//glm::mat4 model;
	// Projection = glm::ortho(-4.0f/3.0f, 4.0f/3.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	cge::Camera camera( app.width, app.height );

	// load and compile our shaders
	cge::Shader spriteShader = cge::ResourceManager::LoadShader( "shaders/cge.vs", "shaders/cge.frag", nullptr, "cge" );

	spriteShader.Use();
	spriteShader.SetMatrix4( "projection", projection );

	// load our texture
	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture( "assets/circle.png", GL_TRUE, "circle" );
	cge::Texture2D chestTexture = cge::ResourceManager::LoadTexture( "assets/chestClosed_W.png", GL_TRUE, "chest" );


	wip::SpriteBatch batch;

	/*
	// define the projection mat4
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(app.width), static_cast<GLfloat>(app.height), 0.0f, -1.0f, 1.0f);

	// load and compile our shaders
	cge::Shader spriteShader = cge::ResourceManager::LoadShader("shaders/cge.vs", "shaders/cge.frag", nullptr, "cge");
	
	spriteShader.Use();
	spriteShader.SetMatrix4("projection", projection);

	// load our texture
	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture("assets/circle.png", GL_TRUE, "circle");

	GLuint quadVBO;
	GLuint quadVAO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	struct Vertex {
		GLfloat x;
		GLfloat y;
		GLfloat uvX;
		GLfloat uvY;
	};

	// start our VAO
	glBindVertexArray(quadVAO);


	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	// tell opengl what attribute arrays we need
	glEnableVertexAttribArray(0);

	// this is the position attribute pointer
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	// end our VAO
	glBindVertexArray(0);

	// now unbind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/


	/*
	// init shaders
	cge::ResourceManager::LoadShader( "shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite" );
	// Configure shaders
	glm::mat4 projection = glm::ortho( 0.0f, static_cast<GLfloat>( app.width ), static_cast<GLfloat>( app.height ), 0.0f, -1.0f, 1.0f );
	cge::ResourceManager::GetShader( "sprite" ).Use().SetInteger( "sprite", 0 );
	cge::ResourceManager::GetShader( "sprite" ).SetMatrix4( "projection", projection );

	cge::Texture2D circleTexture = cge::ResourceManager::LoadTexture( "assets/circle.png", GL_TRUE, "circle" );
	
	// init render data
	GLuint quadVBO;
	GLuint quadVAO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays( 1, &quadVAO );
	glGenBuffers( 1, &quadVBO );

	// bind the VBO and upload the vertex data
	glBindBuffer( GL_ARRAY_BUFFER, quadVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	// bind the VAO and upload the info about the data
	glBindVertexArray( quadVAO );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), (GLvoid*) 0 );

	// unbind the VAO & VBO
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );
	
	cge::Shader spriteShader = cge::ResourceManager::GetShader( "sprite" );

	uni::Circle blackHole( 10.0f, glm::vec2( 625, 400 ), &circleTexture, glm::vec3( 0.0f, 0.5f, 0.8f ) );


	std::vector<uni::Circle> circles;
	circles.emplace_back( 5.0f, glm::vec2( 625, 400 ), &circleTexture, glm::vec3( 0.0f, 0.5f, 0.8f ) );
	circles.emplace_back( 5.0f, glm::vec2( 655, 400 ), &circleTexture, glm::vec3( 0.0f, 0.5f, 0.8f ) );
	circles.emplace_back( 5.0f, glm::vec2( 725, 400 ), &circleTexture, glm::vec3( 0.0f, 0.5f, 0.8f ) );
	circles.emplace_back( 5.0f, glm::vec2( 655, 400 ), &circleTexture, glm::vec3( 0.0f, 0.5f, 0.8f ) );
	*/

	/*
	// we create a quad
	Vertex vertex_topLeft;
	vertex_topLeft.x = 0.5f;
	vertex_topLeft.y = 0.5f;
	vertex_topLeft.uvX = 0.0f;
	vertex_topLeft.uvY = 0.0f;

	Vertex vertex_topRight;
	vertex_topRight.x = 1.0f;
	vertex_topRight.y = 0.5f;
	vertex_topRight.uvX = 1.0f;
	vertex_topRight.uvY = 0.0f;

	Vertex vertex_bottomLeft;
	vertex_bottomLeft.x = 0.5f;
	vertex_bottomLeft.y = 1.0f;
	vertex_bottomLeft.uvX = 0.0f;
	vertex_bottomLeft.uvY = 1.0f;

	Vertex vertex_bottomRight;
	vertex_bottomRight.x = 1.0f;
	vertex_bottomRight.y = 1.0f	;
	vertex_bottomRight.uvX = 1.0f;
	vertex_bottomRight.uvY = 1.0f;

	Vertex vertex_topLeft_2;
	vertex_topLeft_2.x = -0.5f;
	vertex_topLeft_2.y = -0.5f;
	vertex_topLeft_2.uvX = 0.0f;
	vertex_topLeft_2.uvY = 0.0f;

	Vertex vertex_topRight_2;
	vertex_topRight_2.x = -1.0f;
	vertex_topRight_2.y = -0.5f;
	vertex_topRight_2.uvX = 1.0f;
	vertex_topRight_2.uvY = 0.0f;

	Vertex vertex_bottomLeft_2;
	vertex_bottomLeft_2.x = -0.5f;
	vertex_bottomLeft_2.y = -1.0f;
	vertex_bottomLeft_2.uvX = 0.0f;
	vertex_bottomLeft_2.uvY = 1.0f;

	Vertex vertex_bottomRight_2;
	vertex_bottomRight_2.x = -1.0f;
	vertex_bottomRight_2.y = -1.0f;
	vertex_bottomRight_2.uvX = 1.0f;
	vertex_bottomRight_2.uvY = 1.0f;
	*/


	GLfloat delta = helper.getDelta();

	while ( !app.shouldClose() ) {

		// std::cout << 1 / helper.getDelta() << '\n';
		delta = helper.getDelta();

		app.startLoop();

		// camera.Position.x += 0.001f;

		glm::vec2 position( 0.0f, 0.0f );
		glm::vec2 size( 1.0f, 1.0f );
		glm::vec3 color( 1.0f, 1.0f, 1.0f );

		spriteShader.Use(); 
		spriteShader.SetVector3f( "spriteColor", color );
		spriteShader.SetMatrix4( "view", camera.view );

		batch.begin();

		for ( int i = 0; i < 1; i++ )
			batch.draw( position.x, position.y, size.x, size.y, circleTexture.ID );

		batch.end();

		batch.render();

		/*glm::vec3 color(1.0f, 1.0f, 1.0f);

		spriteShader.Use(); spriteShader.SetVector3f("spriteColor", color);
		spriteShader.SetMatrix4("view", camera.view);

		//camera.Position.x += 0.1f;


		// fill our VBO
		std::vector <Vertex> vertices;
		vertices.resize(12); // 12 vertices

		vertices[0] = vertex_topLeft;
		vertices[1] = vertex_topRight;
		vertices[2] = vertex_bottomLeft;
		vertices[3] = vertex_topRight;
		vertices[4] = vertex_bottomRight;
		vertices[5] = vertex_bottomLeft;

		vertices[6] = vertex_topLeft_2;
		vertices[7] = vertex_topRight_2;
		vertices[8] = vertex_bottomLeft_2;
		vertices[9] = vertex_topRight_2;
		vertices[10] = vertex_bottomRight_2;
		vertices[11] = vertex_bottomLeft_2;

		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

		// Orphan the buffer (for speed)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Bind our VAO. This sets up the opengl state we need, including the 
		// vertex attribute pointers and it binds the VBO
		glBindVertexArray(quadVAO);

		circleTexture.Bind();

		glDrawArrays(GL_TRIANGLES, 0, 12);

		glBindVertexArray(0);*/



		/*
		// start of loop
		
		glm::vec2 position( 0.0f, 0.0f );
		glm::vec2 size( 50.0f, 50.0f );
		GLfloat rotate = 0.0f;
		glm::vec3 color( 1.0f, 1.0f, 1.0f );


		glm::mat4 model;

		model = glm::translate( model, glm::vec3( position, 0.0f ) );  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

		//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad

		model = glm::rotate( model, rotate, glm::vec3( 0.0f, 0.0f, 1.0f ) ); // Then rotate

		model = glm::translate( model, glm::vec3( -0.5f * size.x, -0.5f * size.y, 0.0f ) ); // Move origin back

		model = glm::scale( model, glm::vec3( size, 1.0f ) ); // Last scale

		spriteShader.SetMatrix4( "model", model );
		*/

		/*
		spriteShader.Use();
		// Camera
		spriteShader.SetMatrix4( "view", camera.view );

		// Render textured quad
		spriteShader.SetVector3f( "spriteColor", color );

		glActiveTexture( GL_TEXTURE0 );
		circleTexture.Bind();

		glBindVertexArray( quadVAO );
		glDrawArrays( GL_TRIANGLES, 0, 6 );
		glBindVertexArray( 0 );
		*/

		//for ( auto etoile : circles )
		//	etoile.draw( spriteShader, camera, quadVAO );


		camera.updateView();
		app.endLoop();

	}

	return 0;

}