#include "spriteBatch.h"

#include "vertex.h"

namespace cge {

	spriteBatch::spriteBatch()
	{
	}


	spriteBatch::~spriteBatch()
	{
	}

	void spriteBatch::init()
	{

		glGenVertexArrays( 1, &quadVAO );
		glGenVertexArrays( 1, &quadVBO );

		// bind the VAO
		glBindVertexArray( quadVAO );

		// bind the VBO
		glBindBuffer( GL_ARRAY_BUFFER, quadVBO );

		glEnableVertexAttribArray( 0 );

		// tell we'll send a vector4 of floats
		glVertexAttribPointer( 
			0, // use attribute 0
			4, // the size of the vertex
			GL_FLOAT, // type of the vertex value
			GL_FALSE, // no normalization
			4 * sizeof( GLfloat ), // the stride (space between each value)
			(GLvoid*) 0 // no offset (where we start)
		);

		// unbind the VAO & VBO
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );

	}

	void spriteBatch::begin()
	{

		renderBatches.clear();



	}

	void spriteBatch::end()
	{
	}

	void spriteBatch::createRenderBatches()
	{

		if ( quads.empty() )
			return;

		// will store all the vertices we need to upload
		std::vector<cge::Vertex> vertices;

		// vertices.resize( quads.size() *  );

	}

	void spriteBatch::render( cge::Texture2D texture)
	{

		// bind the VAO
		glBindVertexArray( quadVAO );

		texture.Bind();

		// glDrawArrays( GL_TRIANGLES );

			glBindVertexArray( 0 );
	}

}