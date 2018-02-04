#include "SpriteBatch.h"

#include "ResourceManager.h"

#include <algorithm>
#include <iostream>

namespace cge {

	/// Glyph

	Glyph::Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID) {

		// uses the top left corner as anchor

		topLeft.x = x;
		topLeft.y = y;
		topLeft.uvX = 0.0f;
		topLeft.uvY = 1.0f;

		topRight.x = x + width;
		topRight.y = y;
		topRight.uvX = 1.0f;
		topRight.uvY = 1.0f;

		bottomLeft.x = x;
		bottomLeft.y = y + height;
		bottomLeft.uvX = 0.0f;
		bottomLeft.uvY = 0.0f;

		bottomRight.x = x + width;
		bottomRight.y = y + height;
		bottomRight.uvX = 1.0f;
		bottomRight.uvY = 0.0f;

		textureID = _textureID;

	}

	Glyph::Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID, bool inverted) {

		topLeft.x = x;
		topLeft.y = y;
		topLeft.uvX = 1.0f;
		topLeft.uvY = 0.0f;

		topRight.x = x + width;
		topRight.y = y;
		topRight.uvX = 0.0f;
		topRight.uvY = 0.0f;

		bottomLeft.x = x;
		bottomLeft.y = y + height;
		bottomLeft.uvX = 1.0f;
		bottomLeft.uvY = 1.0f;

		bottomRight.x = x + width;
		bottomRight.y = y + height;
		bottomRight.uvX = 0.0f;
		bottomRight.uvY = 1.0f;

		textureID = _textureID;

	}

	Glyph::Glyph(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint _textureID,
		GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
		GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy) {

		// uses the top left corner as anchor

		topLeft.x = x;
		topLeft.y = y;
		topLeft.uvX = topLeftUVx;
		topLeft.uvY = topLeftUVy;

		topRight.x = x + width;
		topRight.y = y;
		topRight.uvX = topRightUVx;
		topRight.uvY = topRightUVy;

		bottomLeft.x = x;
		bottomLeft.y = y + height;
		bottomLeft.uvX = bottomLeftUVx;
		bottomLeft.uvY = bottomLeftUVy;

		bottomRight.x = x + width;
		bottomRight.y = y + height;
		bottomRight.uvX = bottomRightUVx;
		bottomRight.uvY = bottomRightUVy;

		textureID = _textureID;
	}


	/// SpriteBatch

	SpriteBatch::SpriteBatch() {

		// generates a VAO and stores its ID into quadVAO
		glGenVertexArrays(1, &quadVAO);

		// generates a VBO and stores its ID into quadVBO
		glGenBuffers(1, &quadVBO);

		glGenBuffers(1, &quadIBO);

		// create our VAO
		createVAO();

	}

	void SpriteBatch::createVAO() {

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

	Shader SpriteBatch::shader;

	void SpriteBatch::linkShaders(glm::highp_mat4 projection, glm::mat4 view, glm::vec3 color) {

		shader = ResourceManager::loadShader("shaders/cge/SpriteBatchShader.vs", "shaders/cge/SpriteBatchShader.frag", nullptr, "SpriteBatchShader_default");
		shader.setMatrix4("projection", projection);
		shader.setMatrix4("view", view);
		shader.setVector3f("spriteColor", color);

	}

	void SpriteBatch::addGlyph(Glyph newGlyph) {

		glyphs.push_back(newGlyph);

	}

	void SpriteBatch::draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID) {

		glyphs.emplace_back(x, y, width, height, textureID);

	}

	void SpriteBatch::drawInverted(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID) {

		glyphs.emplace_back(x, y, width, height, textureID, true);

	}

	void SpriteBatch::draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID,
		GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
		GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy) {
		glyphs.emplace_back(x, y, width, height, textureID,
			topLeftUVx, topRightUVx, bottomRightUVx, bottomLeftUVx,
			topLeftUVy, topRightUVy, bottomRightUVy, bottomLeftUVy);
	}

	void SpriteBatch::begin() {

		// it makes glyphs.size() == 0, does not free internal memory,
		// so when we later call emplace_back it won't have to call new
		glyphs.clear();

		// same as above
		glyphBatches.clear();

	}

	void SpriteBatch::end() {

		auto g_size = glyphs.size();

		glyphs_map.resize(g_size);

		for (size_t i = 0; i < g_size; i++)
			glyphs_map[i] = &(glyphs[i]);


		// sortGlyphs();

		createGlyphBatches();

	}

	void SpriteBatch::render() {

		glBindVertexArray(quadVAO);

		auto b_size = glyphBatches.size();
		for (size_t i = 0; i < b_size; i++) {
			glBindTexture(GL_TEXTURE_2D, glyphBatches[i].textureID);

			glDrawElementsBaseVertex(GL_TRIANGLES, glyphBatches[i].verticesNumber * 1.5, GL_UNSIGNED_INT, 0, glyphBatches[i].offset);
		}

		glBindVertexArray(0);

	}

	void SpriteBatch::sortGlyphs() {

		std::stable_sort(glyphs_map.begin(), glyphs_map.end(), compareTexture);

	}

	void SpriteBatch::createGlyphBatches() {

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

	bool SpriteBatch::compareTexture(Glyph * a, Glyph * b) {

		return (a->textureID < b->textureID);

	}

}