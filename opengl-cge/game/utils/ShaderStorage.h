#pragma once

#include "../../cge/cge.h"

namespace GAME {

	class ShaderStorage {
	public:
		ShaderStorage(cge::app & app, cge::Camera & camera)
			: spritebatchShader(), spriterendererShader() {

			spritebatchShader = cge::ResourceManager::LoadShader(
				"shaders/spritebatch.vs",
				"shaders/spritebatch.frag",
				nullptr, "spritebatch");
			spritebatchShader.Use();

			spritebatchShader.SetMatrix4(
				"projection",
				glm::ortho(0.0f, static_cast<GLfloat>(app.width),
					0.0f,
					static_cast<GLfloat>(app.height)));

			spritebatchShader.SetMatrix4("view", camera.view);
			spritebatchShader.SetVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));



			spriterendererShader = cge::ResourceManager::LoadShader(
				"shaders/sprite.vs",
				"shaders/sprite.frag",
				nullptr, "sprite");
			spriterendererShader.Use();

			spriterendererShader.SetMatrix4(
				"projection",
				glm::ortho(0.0f, static_cast<GLfloat>(app.width),
					0.0f,
					static_cast<GLfloat>(app.height)));

			spriterendererShader.SetMatrix4("view", camera.view);
			spriterendererShader.SetVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));

		};

		cge::Shader spritebatchShader;
		cge::Shader spriterendererShader;
	};

}