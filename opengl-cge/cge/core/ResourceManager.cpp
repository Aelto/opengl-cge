#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL/SOIL.h>

// Instantiate static variables
std::map<std::string, cge::Texture2D>    cge::ResourceManager::Textures;
std::map<std::string, cge::Shader>       cge::ResourceManager::Shaders;


cge::Shader cge::ResourceManager::LoadShader( const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name ) {

	Shaders[ name ] = loadShaderFromFile( vShaderFile, fShaderFile, gShaderFile );

	return Shaders[ name ];

}

cge::Shader cge::ResourceManager::GetShader( std::string name ) {

	return Shaders[ name ];

}

cge::Texture2D cge::ResourceManager::LoadTexture( const GLchar *file, GLboolean alpha, std::string name ) {

	Textures[ name ] = loadTextureFromFile( file, alpha );

	return Textures[ name ];

}

cge::Texture2D cge::ResourceManager::GetTexture( std::string name ) {

	return Textures[ name ];

}

void cge::ResourceManager::Clear() {

	// (Properly) delete all shaders	
	for ( auto iter : Shaders )
		glDeleteProgram( iter.second.ID );

	// (Properly) delete all textures
	for ( auto iter : Textures )
		glDeleteTextures( 1, &iter.second.ID );

}

cge::Shader cge::ResourceManager::loadShaderFromFile( const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile ) {

	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try	{
		// Open files
		std::ifstream vertexShaderFile( vShaderFile );
		std::ifstream fragmentShaderFile( fShaderFile );
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
		if ( gShaderFile != nullptr )
		{
			std::ifstream geometryShaderFile( gShaderFile );
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	} catch ( std::exception e ) {
		std::cout << "ERROR::SHADER: Failed to read shader files, path: " << vShaderFile << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();

	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile( vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr );

	return shader;

}

cge::Texture2D cge::ResourceManager::loadTextureFromFile( const GLchar *file, GLboolean alpha ) {

	// Create Texture object
	Texture2D texture;
	if ( alpha ) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	
	// Now generate texture
	texture.Generate(width, height, image);
	
	// And finally free image data
	SOIL_free_image_data(image);

	return texture;

}