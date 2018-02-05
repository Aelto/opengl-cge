#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "character.h"
#include "text-manager.h"

namespace cge {

	class Text {
	private:
		TextManager * manager;

	public:
    glm::vec2 position;
		GLfloat scale;
		glm::vec3 color;
		std::string string;
    
		Text(char* text, TextManager * manager, GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1, glm::vec3 color = glm::vec3(1, 1, 1)) {
      this->manager = manager;
      this->position = glm::vec2(x, y);
      this->scale = scale;
      this->color = color;
      setString(text);
    }

		void render() {
      manager->renderText(string, position.x, position.y, scale, color);
    }

		void setString(char * text) {
      string = std::string(text);
    }

	};


}