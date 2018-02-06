#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <vector>

#include "shader.h"
#include "spritebatch.h"
#include "camera.h"
#include "quad.h"

namespace cge {

	class SpriteRenderer {
	public:
		std::vector<Quad> quads;
		GLuint quadVAO;
		GLuint quadVBO;
		GLuint quadIBO;

		SpriteRenderer() {
      glGenVertexArrays(1, &quadVAO);
      glGenBuffers(1, &quadVBO);
      glGenBuffers(1, &quadIBO);

      // VAO creation
      glBindVertexArray(quadVAO);
      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

      // it's a vector4 ( X_position, Y_position, X_uv_coordinates, Y_uv_coordinates )
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

		void begin() {
      quads.clear();
    }

		void end() {
      std::vector<Vertex> vertices;
      vertices.resize(quads.size() * 4);

      std::vector<GLuint> indices;
      indices.resize(quads.size() * 6);

      if (quads.empty())
        return;

      int offset = 0;
      int currentVertex = 0;
      int currentIndex = 0;

      auto quad_size = quads.size();
      for (size_t currentQuad = 0; currentQuad < quad_size; currentQuad++) {

        indices[currentIndex++] = currentVertex;
        indices[currentIndex++] = currentVertex + 1;
        indices[currentIndex++] = currentVertex + 3;
        indices[currentIndex++] = currentVertex + 1;
        indices[currentIndex++] = currentVertex + 2;
        indices[currentIndex++] = currentVertex + 3;

        vertices[currentVertex++] = quads[currentQuad].topRight;
        vertices[currentVertex++] = quads[currentQuad].bottomRight;
        vertices[currentVertex++] = quads[currentQuad].bottomLeft;
        vertices[currentVertex++] = quads[currentQuad].topLeft;

        offset += 4;

      }

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, (currentIndex + 1) * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
      glBufferData(GL_ARRAY_BUFFER, (currentVertex + 1) * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
      glBufferSubData(GL_ARRAY_BUFFER, 0, (currentVertex + 1) * sizeof(Vertex), vertices.data());
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

		void render(Shader & shader, Camera & camera) {
      if (quads.empty())
        return;

      glBindVertexArray(quadVAO);
      GLuint lastTexture = GL_TEXTURE0;

      size_t quad_size = quads.size();
      for (size_t currentQuad = 0; currentQuad < quad_size; currentQuad++) {
        glm::mat4 model;
        
        model = glm::translate(model, glm::vec3(quads[currentQuad].x, quads[currentQuad].y, 0.0f));
        model = glm::translate(model, glm::vec3(0.5f * quads[currentQuad].width, 0.5f * quads[currentQuad].height, 0.0f));
        model = glm::rotate(model, quads[currentQuad].rotate, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * quads[currentQuad].width, -0.5f * quads[currentQuad].height, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

        shader.setMatrix4("model", model);
        // shader.setVector3f("color", glm::vec3(1.0f, 1.0f, 1.0f));

        if (quads[currentQuad].textureID != lastTexture) {
          glBindTexture(GL_TEXTURE_2D, quads[currentQuad].textureID);
          lastTexture = quads[currentQuad].textureID;
        }

        glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, currentQuad * 6);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
      }

      glBindVertexArray(0);
    }

		void draw(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLuint textureID,
			GLfloat topLeftUVx, GLfloat topRightUVx, GLfloat bottomRightUVx, GLfloat bottomLeftUVx,
			GLfloat topLeftUVy, GLfloat topRightUVy, GLfloat bottomRightUVy, GLfloat bottomLeftUVy, GLfloat rotate) {
      quads.emplace_back(x, y, width, height, textureID,
        topLeftUVx, topRightUVx,
        bottomRightUVx, bottomLeftUVx,
        topLeftUVy, topRightUVy, bottomRightUVy, bottomLeftUVy, rotate);
    }

	};

}