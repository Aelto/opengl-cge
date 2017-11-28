#pragma once

#include "Shader.h"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include <unordered_map>
#include <vector>

namespace cge {

	struct Vertex {
		GLfloat x;
		GLfloat y;
		GLfloat uvX;
		GLfloat uvY;
	};

	class Glyph {
	public:
		Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID);
		Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID, bool inverted);
		Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy);

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomRight;
		Vertex bottomLeft;

		GLuint textureID;
	};

	class GlyphBatch {
	public:
		GlyphBatch(GLuint _textureID, GLuint _verticesNumber, GLuint _offset)
			: textureID(_textureID), verticesNumber(_verticesNumber), offset(_offset) {}

		GLuint textureID;
		GLuint verticesNumber;
		GLuint offset;
	};

	class SpriteBatch {
	public:
		SpriteBatch();

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
		 * Stores a cge::Shader object to hold and use as
		 * default fragment and vertex shaders
		 */
		static Shader shader;

		/// methods

		/**
		 * Set up the VAO we need to use our VBO and shaders
		 */
		void createVAO();

		/**
		 *
		 */
		static void linkShaders(glm::highp_mat4 projection, glm::mat4 view, glm::vec3 color);

		/**
		 * Copy a glyph into the this->glyphs vector
		 * this is not the recommended way to add a glyph
		 */
		void addGlyph(Glyph newGlyph);

		/**
		 * Get a set of data and emplace_back a Glyph into this->glyphs
		 * vector with this data as parameter
		 */
		void draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID);
		void drawInverted(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID);
		void draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy);

		/**
		 * Set up everything to begin the spritebatch collecting
		 */
		void begin();

		/**
		 * Set up everything for the this->render();
		 * Upload the data with the VBO
		 */
		void end();

		/**
		 * Uses
		 */
		void render();

		void sortGlyphs();

		void createGlyphBatches();

		static bool compareTexture(Glyph* a, Glyph* b);

	};

}