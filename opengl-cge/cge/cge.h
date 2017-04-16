#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

// Classes used for the rendering engine
#include "core\app.h"
#include "core\helper.h"
#include "core\camera.h"
#include "core\ResourceManager.h"
#include "core\Shader.h"
#include "core\Texture.h"
#include "core\SpriteBatch.h"

// Classes used for the game engine
#include "game\Sprite.h"
#include "game\Hitbox.h"
#include "game\SpriteSheetUV.h"
#include "game\SpriteSheet.h"
#include "game\AnimationsUV.h"
#include "game\SpriteAnimation.h"