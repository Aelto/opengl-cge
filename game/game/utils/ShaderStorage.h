#pragma once

#include "../../src/cge.h"

namespace GAME {

	class ShaderStorage {
	public:
		ShaderStorage(cge::App & app, cge::Camera & camera)
			: spritebatchShader(), spriterendererShader() {

			spritebatchShader = cge::ResourceManager::loadShader(
				"shaders/spritebatch.vs",
				"shaders/spritebatch.frag",
				nullptr, "spritebatch");
			spritebatchShader.use();

			spritebatchShader.setMatrix4(
				"projection",
				glm::ortho(0.0f, static_cast<GLfloat>(app.width),
					0.0f,
					static_cast<GLfloat>(app.height)));

			spritebatchShader.setMatrix4("view", camera.view);
			spritebatchShader.setVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));



			spriterendererShader = cge::ResourceManager::loadShader(
				"shaders/sprite.vs",
				"shaders/sprite.frag",
				nullptr, "sprite");
			spriterendererShader.use();

			spriterendererShader.setMatrix4(
				"projection",
				glm::ortho(0.0f, static_cast<GLfloat>(app.width),
					0.0f,
					static_cast<GLfloat>(app.height)));

			spriterendererShader.setMatrix4("view", camera.view);
			spriterendererShader.setVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));

		};

		cge::Shader spritebatchShader;
		cge::Shader spriterendererShader;
	};

}