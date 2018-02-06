#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Classes used for the rendering engine
#include "core/app.h"
#include "core/helper.h"
#include "core/camera.h"
#include "core/ResourceManager.h"
#include "core/Shader.h"
#include "core/Texture.h"
#include "core/SpriteBatch.h"
#include "core/SpriteRenderer.h"
#include "core/Text.h"

// Classes used for the game engine
#include "core/Sprite.h"
#include "core/Hitbox.h"
#include "core/SpriteSheetUV.h"
#include "core/SpriteSheet.h"
#include "core/AnimationsUV.h"
#include "core/SpriteAnimation.h"