#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

#include <map>
#include <iostream>
#include <string>

namespace cge {

	struct Character {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
	};

	class Text;

	class TextManager {
	public:
		TextManager();

		bool init(GLuint width, GLuint height);
		void renderText(std::string & text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 & color);
		Text newText(char* text, GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1, glm::vec3 color = glm::vec3(1, 1, 1));

	private:
		std::map<GLchar, Character> characters;
		GLuint VAO, VBO;
		Shader shader;
	};

	class Text {
	public:
		Text(char* text, TextManager * manager, GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1, glm::vec3 color = glm::vec3(1, 1, 1));

		void render();
		void setString(char * text);
		glm::vec2 position;
		GLfloat scale;
		glm::vec3 color;
		std::string string;

	private:
		TextManager * manager;
	};


}