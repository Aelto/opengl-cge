#include "SpriteRenderer.h"

cge::Quad::Quad(GLfloat x, GLfloat y, 
	GLfloat _width, GLfloat _height, GLuint _textureID,
	GLfloat topLeftUVx, GLfloat topRightUVx,
	GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
	GLfloat topLeftUVy, GLfloat topRightUVy,
	GLfloat bottomRightUVy, GLfloat bottomLeftUVy, GLfloat _rotate) {

	width = _width;
	height = _height;

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
	rotate = _rotate;

}


cge::SpriteRenderer::SpriteRenderer() {

	glGenVertexArrays(1, &quadVAO);

	glGenBuffers(1, &quadVBO);

	// VAO creation
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	// it's a vector4 ( X_position, Y_position, X_uv_coordinates, Y_uv_coordinates )
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void cge::SpriteRenderer::draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID,
	GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
	GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy, GLfloat rotate) {

	quads.emplace_back(x, y, width, height, textureID,
		topLeftUVx, topRightUVx,
		bottomRightUVx, bottomLeftUVx,
		topLeftUVy, topRightUVy, bottomRightUVy, bottomLeftUVy, rotate);

}

void cge::SpriteRenderer::begin() {

	quads.clear();

}

void cge::SpriteRenderer::end() {

	std::vector<Vertex> vertices;
	vertices.resize(quads.size() * 6);

	if (quads.empty())
		return;
	int currentVertex = 0;

	vertices[currentVertex++] = quads[0].topLeft;
	vertices[currentVertex++] = quads[0].topRight;
	vertices[currentVertex++] = quads[0].bottomLeft;
	vertices[currentVertex++] = quads[0].topRight;
	vertices[currentVertex++] = quads[0].bottomRight;
	vertices[currentVertex++] = quads[0].bottomLeft;

	auto quad_size = quads.size();
	for (size_t currentQuad = 1; currentQuad < quad_size; currentQuad++) {

		vertices[currentVertex++] = quads[currentQuad].topLeft;
		vertices[currentVertex++] = quads[currentQuad].topRight;
		vertices[currentVertex++] = quads[currentQuad].bottomLeft;
		vertices[currentVertex++] = quads[currentQuad].topRight;
		vertices[currentVertex++] = quads[currentQuad].bottomRight;
		vertices[currentVertex++] = quads[currentQuad].bottomLeft;

	}

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void cge::SpriteRenderer::render(Shader & shader) {

	if (quads.empty())
		return;

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(quadVAO);
	GLuint lastTexture = GL_TEXTURE0;

	auto quad_size = quads.size();
	for (size_t currentQuad = 0; currentQuad < quad_size; currentQuad++) {
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(quads[currentQuad].topLeft.x, quads[currentQuad].topLeft.y, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * quads[currentQuad].width, 0.5f * quads[currentQuad].height, 0.0f));
		model = glm::rotate(model, quads[currentQuad].rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * quads[currentQuad].width, -0.5f * quads[currentQuad].height, 0.0f));

		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		shader.SetMatrix4("model", model);

		if (quads[currentQuad].textureID != lastTexture) {
			glBindTexture(GL_TEXTURE_2D, quads[currentQuad].textureID);
			lastTexture = quads[currentQuad].textureID;
		}
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);

}

