#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace cge {

	class Shader {
	public:
		GLuint ID;

		Shader() {}

		Shader & use() {
      glUseProgram(this->ID);
      return *this;
    }

		void compile(const GLchar *vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource = nullptr) {
      GLuint sVertex, sFragment, gShader;
      
      // Vertex Shader
      sVertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(sVertex, 1, &vertexSource, NULL);
      glCompileShader(sVertex);
      checkCompileErrors(sVertex, "VERTEX");
      
      // Fragment Shader
      sFragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(sFragment, 1, &fragmentSource, NULL);
      glCompileShader(sFragment);
      checkCompileErrors(sFragment, "FRAGMENT");
      
      // If geometry shader source code is given, also compile geometry shader
      if (geometrySource != nullptr) {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
      }
      
      // Shader Program
      this->ID = glCreateProgram();
      glAttachShader(this->ID, sVertex);
      glAttachShader(this->ID, sFragment);
      if (geometrySource != nullptr)
        glAttachShader(this->ID, gShader);
      glLinkProgram(this->ID);
      checkCompileErrors(this->ID, "PROGRAM");
      
      // Delete the shaders as they're linked into our program now and no longer necessery
      glDeleteShader(sVertex);
      glDeleteShader(sFragment);
      if (geometrySource != nullptr)
        glDeleteShader(gShader);
    }

		void setFloat(const GLchar * name, GLfloat value, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform1f(glGetUniformLocation(this->ID, name), value);
    }

		void setInteger(const GLchar * name, GLint value, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform1i(glGetUniformLocation(this->ID, name), value);
    }

		void setVector2f(const GLchar * name, GLfloat x, GLfloat y, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform2f(glGetUniformLocation(this->ID, name), x, y);
    }

		void setVector2f(const GLchar * name, const glm::vec2 & value, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
    }

		void setVector3f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
    }

		void setVector3f(const GLchar * name, const glm::vec3 & value, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
    }

		void setVector4f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
    }

		void setVector4f(const GLchar * name, const glm::vec4 & value, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
    }

		void setMatrix4(const GLchar * name, const glm::mat4 & matrix, GLboolean useShader = false) {
      if (useShader)
        this->use();
      glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

	private:
		void checkCompileErrors(GLuint object, std::string type) {
      GLint success;
      GLchar infoLog[1024];
      if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
          glGetShaderInfoLog(object, 1024, NULL, infoLog);
          std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
            << infoLog << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
      }
      else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
          glGetProgramInfoLog(object, 1024, NULL, infoLog);
          std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
            << infoLog << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
      }
    }
	};

}