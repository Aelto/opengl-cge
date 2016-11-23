#include "SpriteBatch.h"

#include <algorithm>
#include <iostream>

namespace cge {

	/// Glyph

	Glyph::Glyph( GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID ) {

		// uses the top left corner as anchor

		topLeft.x = x - width / 2.0f;
		topLeft.y = y - height / 2.0f;
		topLeft.uvX = 0.0f;
		topLeft.uvY = 1.0f;

		topRight.x = x + width / 2.0f;
		topRight.y = y - height / 2.0f;
		topRight.uvX = 1.0f;
		topRight.uvY = 1.0f;

		bottomLeft.x = x - width / 2.0f;
		bottomLeft.y = y + height / 2.0f;
		bottomLeft.uvX = 0.0f;
		bottomLeft.uvY = 0.0f;

		bottomRight.x = x + width / 2.0f;
		bottomRight.y = y + height / 2.0f;
		bottomRight.uvX = 1.0f;
		bottomRight.uvY = 0.0f;

		textureID = _textureID;

	}


	/// SpriteBatch

	SpriteBatch::SpriteBatch()
	{

		// generates a VAO and stores its ID into quadVAO
		glGenVertexArrays( 1, &quadVAO );

		// generates a VBO and stores its ID into quadVBO
		glGenBuffers( 1, &quadVBO );

		// create our VAO
		createVAO();

	}

	void SpriteBatch::createVAO()
	{

		// We bind our VAO
		// Everything we do now will be stored into the VAO
		glBindVertexArray( quadVAO );

		glBindBuffer( GL_ARRAY_BUFFER, quadVBO );
		// tell opengl what attribute arrays we need
		glEnableVertexAttribArray( 0 );

		// this is the position attribute pointer
		// it's a vector4 ( X_position, Y_position, X_uv_coordinates, Y_uv_coordinates )
		glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), (GLvoid*) 0 );

		// Unbind the VAO
		glBindVertexArray( 0 );

		// We unbind the VBO outside of the VAO
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

	}

	void SpriteBatch::addGlyph( Glyph newGlyph )
	{

		glyphs.push_back( newGlyph );

	}

	void SpriteBatch::draw( GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID )
	{

		glyphs.emplace_back( x, y, width, height, textureID );

	}

	void SpriteBatch::begin()
	{

		// it makes glyphs.size() == 0, does not free internal memory,
		// so when we later call emplace_back it won't have to call new
		glyphs.clear();

		// same as above
		glyphBatches.clear();

	}

	void SpriteBatch::end()
	{

		auto g_size = glyphs.size();

		glyphs_map.resize( g_size );

		for ( size_t i = 0; i < g_size; i++ )
			glyphs_map[ i ] = &( glyphs[ i ] );


		// sortGlyphs();

		createGlyphBatches();

	}

	void SpriteBatch::render()
	{

		// Bind our VAO. This sets up the opengl state we need, including the 
		// vertex attribute pointers and it binds the VBO
		glBindVertexArray( quadVAO );

		auto b_size = glyphBatches.size();

		for ( size_t i = 0; i < b_size; i++ ) {

			int b = 1;

			glBindTexture( GL_TEXTURE_2D, glyphBatches[ i ].textureID );

			glDrawArrays( GL_TRIANGLES, glyphBatches[ i ].offset, glyphBatches[ i ].verticesNumber );

		}

		glBindVertexArray( 0 );

	}

	void SpriteBatch::sortGlyphs()
	{

		std::stable_sort( glyphs_map.begin(), glyphs_map.end(), compareTexture );

	}

	void SpriteBatch::createGlyphBatches()
	{

		// prepare the list of vertices we'll send to the gpu
		std::vector<Vertex> vertices;
		vertices.resize( glyphs_map.size() * 6 );


		if ( glyphs_map.empty() )
			return;

		int offset = 0; // current offset
		int cv = 0; // current vertex

		//Add the first batch
		glyphBatches.emplace_back( glyphs_map[ 0 ]->textureID, 6, offset );
		vertices[ cv++ ] = glyphs_map[ 0 ]->topLeft;
		vertices[ cv++ ] = glyphs_map[ 0 ]->topRight;
		vertices[ cv++ ] = glyphs_map[ 0 ]->bottomLeft;
		vertices[ cv++ ] = glyphs_map[ 0 ]->topRight;
		vertices[ cv++ ] = glyphs_map[ 0 ]->bottomRight;
		vertices[ cv++ ] = glyphs_map[ 0 ]->bottomLeft;
		offset += 6;

		auto g_size = glyphs_map.size();
		//Add all the rest of the glyphs
		for ( size_t cg = 1; cg < g_size; cg++ ) {

			// Check if this glyph can be part of the current batch
			if ( glyphs_map[ cg ]->textureID != glyphs_map[ cg - 1 ]->textureID ) {
				// Make a new batch
				glyphBatches.emplace_back( glyphs_map[ cg ]->textureID, 6, offset );
			} else {
				// If its part of the current batch, just increase numVertices
				glyphBatches.back().verticesNumber += 6;
			}
			vertices[ cv++ ] = glyphs_map[ cg ]->topLeft;
			vertices[ cv++ ] = glyphs_map[ cg ]->topRight;
			vertices[ cv++ ] = glyphs_map[ cg ]->bottomLeft;
			vertices[ cv++ ] = glyphs_map[ cg ]->topRight;
			vertices[ cv++ ] = glyphs_map[ cg ]->bottomRight;
			vertices[ cv++ ] = glyphs_map[ cg ]->bottomLeft;
			offset += 6;
		}

		// Bind our VBO
		glBindBuffer( GL_ARRAY_BUFFER, quadVBO );

		// Orphan the buffer (for speed)
		glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), nullptr, GL_DYNAMIC_DRAW );
		// Upload the data
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertices.size() * sizeof( Vertex ), vertices.data() );

		// Unbind the VBO
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

	}

	bool SpriteBatch::compareTexture( Glyph * a, Glyph * b ) {

		return ( a->textureID < b->textureID );

	}

}