#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

#include "texture.h"
#include "shader.h"
#include "spritebatch.h"
#include "hitbox.h"

namespace cge {

	class Sprite {
	public:
		glm::vec2 position;

		glm::vec2 size;

		glm::vec3 color;

		GLfloat rotate;

		cge::Texture2D * texture;

		cge::Hitbox * box;

    Sprite()
  		: position(0.0f, 0.0f), size(10.0f, 10.0f), texture(nullptr), box(nullptr) {}
		
    Sprite(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture)
		  : position(pos), size(size), texture(_texture), box(nullptr) {}

		/**
		 * Give to the suppplied SpriteBatch enough informations
		 * to be able to create vertices for this object
		 */
		virtual void batchDraw(cge::SpriteBatch & spriteBatch) {
      spriteBatch.draw(position.x, position.y, size.x, size.y, texture->ID);
    }

		/**
		 * Get a glm::vec2 with the distance relative to this->position
		 * between this->position and another glm::vec2
		 */
		glm::vec2 distanceTo(const glm::vec2 & pos) {
      return glm::vec2(position.x - pos.x, position.y - pos.y);
    }

		/**
		 * Get whether or not "this" does intersect
		 * with another Sprite
		 */
		bool intersects(const Sprite & obj) {
      if (box == nullptr)
        return false;

      return box->intersects(obj.box, position, obj.position, size, obj.size);
    }

		/**
		 * Resolve the collision so "this" and "obj" don't
		 * touch anymore by moving "this"
		 */
		void resolve(Sprite & obj) {
      box->resolve(obj.box, position, obj.position);
    }

		/**
		 * Create a list of boxes based on the data supplied
		 * It needs a vector of relative positions and a vector of sizes,
		 * these two vectors must have the same size
		 */
		void addBox(Hitbox * _box) {
      box = _box;
    }
	};

}