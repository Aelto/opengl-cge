#pragma once

#include "../../cge/cge.h"

namespace GAME {

	class ShaderStorage {
	public:
		ShaderStorage(cge::app & app, cge::Camera & camera)
			: defaultShader() {

			defaultShader = cge::ResourceManager::LoadShader(
				"shaders/cge.vs",
				"shaders/cge.frag",
				nullptr, "cge");
			defaultShader.Use();

			defaultShader.SetMatrix4(
				"projection",
				glm::ortho(0.0f, static_cast<GLfloat>(app.width),
					0.0f,
					static_cast<GLfloat>(app.height)));

			defaultShader.SetMatrix4("view", camera.view);
			defaultShader.SetVector3f("spriteColor", glm::vec3(1.0f, 1.0f, 1.0f));

		};

		cge::Shader defaultShader;
	};

}