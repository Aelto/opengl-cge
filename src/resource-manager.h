#pragma once


#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include <SOIL/SOIL.h>

#include "Texture.h"
#include "Shader.h"


namespace cge {

	class ResourceManager {
	public:

		/**
		 * Resource storage
		 */
		static std::map<std::string, Shader>    shaders;
		static std::map<std::string, Texture2D> textures;

		/**
		 * Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
		 * If gShaderFile is not nullptr, it also loads a geometry shader
		 */
		static Shader loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
      shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);

      return shaders[name];
    }

		/**
		 * Retrieves a stored sader
		 */
		static Shader getShader(std::string name) {
      return shaders[name];
    }

		/**
		 * Loads (and generates) a texture from file
		 */
		static Texture2D loadTexture(const GLchar *file, GLboolean alpha, std::string name) {
      textures[name] = loadTextureFromFile(file, alpha);

      return textures[name];
    }

		/**
		 * Retrieves a stored texture
		 */
		static Texture2D getTexture(std::string name) {
      return textures[name];
    }

		/**
		 * Properly de-allocates all loaded resources
		 */
		static void clear() {
      for (auto iter : shaders)
  			glDeleteProgram(iter.second.ID);

  		for (auto iter : textures)
	  		glDeleteTextures(1, &iter.second.ID);
	  }

	private:

		/**
		 * Private constructor, that is we do not want any actual resource manager objects.
		 * Its members and functions should be publicly available (static).
		 */
		ResourceManager() {}

		/**
		 * Loads and generates a shader from file
		 */
		static Shader loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile = nullptr) {

      // 1. Retrieve the vertex/fragment source code from filePath
      std::string vertexCode;
      std::string fragmentCode;
      std::string geometryCode;
      try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr) {
          std::ifstream geometryShaderFile(gShaderFile);
          std::stringstream gShaderStream;
          gShaderStream << geometryShaderFile.rdbuf();
          geometryShaderFile.close();
          geometryCode = gShaderStream.str();
        }
      }
      catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files, path: " << vShaderFile << std::endl;
      }

      const GLchar *vShaderCode = vertexCode.c_str();
      const GLchar *fShaderCode = fragmentCode.c_str();
      const GLchar *gShaderCode = geometryCode.c_str();

      // 2. Now create shader object from source code
      Shader shader;
      shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

      return shader;

    }

		/**
		 * Loads a single texture from file
		 */
		static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha) {

      // Create Texture object
      Texture2D texture;
      if (alpha) {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
      }

      // Load image
      int width, height;
      unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

      // Now generate texture
      texture.generate(width, height, image);

      // And finally free image data
      SOIL_free_image_data(image);

      return texture;

    }
	};

}