#pragma once

#include <vector>

#include <GL/glew.h>

#include "vertex.h"
#include "glyph.h"
#include "glyph-batch.h"

namespace cge {

  	class SpriteBatch {
	public:
		SpriteBatch() {

		// generates a VAO and stores its ID into quadVAO
		glGenVertexArrays(1, &quadVAO);

		// generates a VBO and stores its ID into quadVBO
		glGenBuffers(1, &quadVBO);

		glGenBuffers(1, &quadIBO);

		// create our VAO
		createVAO();
	}

		/// props

		/**
		 * A list of Glyphs which contain 4 vertices each
		 *
		 */
		std::vector<Glyph> glyphs;

		/**
		* A list of pointers of the Glyphs in this->glyphs
		* Allows fast sorting without moving huge sets of data
		*/
		std::vector<Glyph *> glyphs_map;

		/**
		 * A list of glyphBatches that will be used when rendering
		 */
		std::vector<GlyphBatch> glyphBatches;

		/**
		 * Stores the id of the VAO the SpriteBatch uses
		 */
		GLuint quadVAO;

		/**
		 * Stores the id of the VAO used by the SpriteBatch
		 */
		GLuint quadVBO;

		GLuint quadIBO;

		/**
		 * Set up the VAO we need to use our VBO and shaders
		 */
		void createVAO() {
      glBindVertexArray(quadVAO);

      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
      glEnableVertexAttribArray(0);

      // this is the position attribute pointer
      // it's a vector4 ( X_position, Y_position, X_uv_coordinates, Y_uv_coordinates )
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

      glBindVertexArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

		/**
		 * Copy a glyph into the this->glyphs vector
		 * this is not the recommended way to add a glyph
		 */
		void addGlyph(Glyph newGlyph) {
      glyphs.push_back(newGlyph);
    }

		/**
		 * Get a set of data and emplace_back a Glyph into this->glyphs
		 * vector with this data as parameter
		 */
		void draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID) {
      glyphs.emplace_back(x, y, width, height, textureID);
    }

		void drawInverted(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID) {
      glyphs.emplace_back(x, y, width, height, textureID, true);
    }

		void draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy) {
      glyphs.emplace_back(x, y, width, height, textureID,
        topLeftUVx, topRightUVx, bottomRightUVx, bottomLeftUVx,
        topLeftUVy, topRightUVy, bottomRightUVy, bottomLeftUVy);
    }

		/**
		 * Set up everything to begin the spritebatch collecting
		 */
		void begin() {
      glyphs.clear();
      glyphBatches.clear();
    }

		/**
		 * Set up everything for the this->render();
		 * Upload the data with the VBO
		 */
		void end() {
  		auto g_size = glyphs.size();

	  	glyphs_map.resize(g_size);

		  for (size_t i = 0; i < g_size; i++)
			  glyphs_map[i] = &(glyphs[i]);

  		// sortGlyphs();

	  	createGlyphBatches();
	  }

		/**
		 * Uses
		 */
		void render() {
      glBindVertexArray(quadVAO);

      auto b_size = glyphBatches.size();
      for (size_t i = 0; i < b_size; i++) {
        glBindTexture(GL_TEXTURE_2D, glyphBatches[i].textureID);

        glDrawElementsBaseVertex(GL_TRIANGLES, glyphBatches[i].verticesNumber * 1.5, GL_UNSIGNED_INT, 0, glyphBatches[i].offset);
      }

      glBindVertexArray(0);
    }

		void sortGlyphs() {
      std::stable_sort(glyphs_map.begin(), glyphs_map.end(), compareTexture);
    }

		void createGlyphBatches() {
      // prepare the list of vertices we'll send to the gpu
      std::vector<Vertex> vertices;
      vertices.resize(glyphs_map.size() * 4);

      std::vector<GLuint> indices;
      indices.resize(glyphs_map.size() * 6);

      if (glyphs_map.empty())
        return;

      int offset = 0; // current offset
      int cv = 0; // current vertex
      int ci = 0; // current index

      //Add the first batch
      glyphBatches.emplace_back(glyphs_map[0]->textureID, 4, offset);

      indices[ci++] = cv;
      indices[ci++] = cv + 1;
      indices[ci++] = cv + 3;
      indices[ci++] = cv + 1;
      indices[ci++] = cv + 2;
      indices[ci++] = cv + 3;

      vertices[cv++] = glyphs_map[0]->topRight;
      vertices[cv++] = glyphs_map[0]->bottomRight;
      vertices[cv++] = glyphs_map[0]->bottomLeft;
      vertices[cv++] = glyphs_map[0]->topLeft;
      offset += 4;

      auto g_size = glyphs_map.size();
      //Add all the rest of the glyphs
      for (size_t cg = 1; cg < g_size; cg++) {

        // check if this glyph can be part of the current batch
        if (glyphs_map[cg]->textureID != glyphs_map[cg - 1]->textureID) {
          // make a new batch
          glyphBatches.emplace_back(glyphs_map[cg]->textureID, 4, offset);
        }
        else {
          // if its part of the current batch, just increase numVertices
          glyphBatches.back().verticesNumber += 4;
        }

        indices[ci++] = cv;
        indices[ci++] = cv + 1;
        indices[ci++] = cv + 3;
        indices[ci++] = cv + 1;
        indices[ci++] = cv + 2;
        indices[ci++] = cv + 3;

        vertices[cv++] = glyphs_map[cg]->topRight;
        vertices[cv++] = glyphs_map[cg]->bottomRight;
        vertices[cv++] = glyphs_map[cg]->bottomLeft;
        vertices[cv++] = glyphs_map[cg]->topLeft;
        offset += 4;
      }

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ci + 1) * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
      glBufferData(GL_ARRAY_BUFFER, (cv + 1) * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
      glBufferSubData(GL_ARRAY_BUFFER, 0, (cv + 1) * sizeof(Vertex), vertices.data());
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

		static bool compareTexture(Glyph* a, Glyph* b) {
      return (a->textureID < b->textureID);
    }

	};

}