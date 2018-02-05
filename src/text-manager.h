#pragma once

#include <map>
#include <iostream>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "character.h"
#include "resource-manager.h"

namespace cge {

  class Text;

	class TextManager {
  private:
		std::map<GLchar, Character> characters;
		GLuint VAO, VBO;
		Shader shader;

	public:
		TextManager() {
      shader = ResourceManager::loadShader("shaders/text.vs", "shaders/text.frag", nullptr, "cge_textShader");
      shader.use();
    }

		bool init(GLuint width, GLuint height) {
      shader.use();
      glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
      glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

      FT_Library ft;
      if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
      }

      FT_Face face;
      if (FT_New_Face(ft, "arial.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
      }

      FT_Set_Pixel_Sizes(face, 0, 14); // font size

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

      for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
          std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
          continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_RED,
          face->glyph->bitmap.width,
          face->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        Character character = {
          texture,
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(c, character));
      }

      glBindTexture(GL_TEXTURE_2D, 0);
      FT_Done_Face(face);
      FT_Done_FreeType(ft);

      // Configure VAO/VBO for texture quads
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      return true;
    }
    
		void renderText(std::string & text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 & color) {
      // Activate corresponding render state	
      shader.use();
      glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(VAO);

      // Iterate through all characters
      std::string::const_iterator c;
      for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
          { xpos,     ypos + h,   0.0, 0.0 },
          { xpos,     ypos,       0.0, 1.0 },
          { xpos + w, ypos,       1.0, 1.0 },

          { xpos,     ypos + h,   0.0, 0.0 },
          { xpos + w, ypos,       1.0, 1.0 },
          { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
      }
      glBindVertexArray(0);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
	};

}