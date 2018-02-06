#pragma once

#include <GL/glew.h>

#include "texture.h"

namespace cge {

	/**
	 * A SpriteSheetUV object allows easy management of the UV coordinates of a texture
	 *
	 */
	class SpriteSheetUV {
	public:

		/**
		 * Stores how many rows are in the spritesheet
		 */
		int rows;

		/**
		 * Stores how many columns are in the spritesheet
		 */
		int columns;

		/**
		 * Stores how many cells are in the spritesheet
		 */
		int cells;

		/**
		 * Stores how many tick() calls are needed before it goes to the next cell
		 */
		float timePerCell;

		/**
		 * Stores the current position in the rows
		 */
		int currentRow;

		/**
		 * Stores the current position in the columns
		 */
		int currentColumn;

		/**
		 * Stores which cell we're currently on
		 */
		int currentCell;

		/**
		 * Stores the tick numbers received for the current cell
		 */
		float currentTime;

		/**
		 * Precompute how much a cell is on the X axis for the UV coordinates
		 */
		GLfloat xMultiplier;

		/**
		 * Precompute how much a cell is on the Y axis for the UV coordinates
		 */
		GLfloat yMultiplier;

		SpriteSheetUV() {}

		SpriteSheetUV(int _rows, int _columns, float _timePerCell, int _cells = -1) {
      rows = _rows;
      columns = _columns;

      if (_cells == -1 || _cells > rows * columns) {
        cells = rows * columns;
      }
      else cells = _cells;

      currentCell = 0;
      currentRow = 0;
      currentColumn = 0;
      currentTime = 0.0f;

      timePerCell = _timePerCell;

      // precompute the X and Y values of a cells
      xMultiplier = 1.0f / columns;
      yMultiplier = 1.0f / rows;
    }

		// copy constructor
		SpriteSheetUV(const SpriteSheetUV & obj) {
      rows = obj.rows;
      columns = obj.columns;

      if (obj.cells == -1 || obj.cells > rows * columns) {
        cells = rows * columns;
      }
      else cells = obj.cells;

      currentCell = obj.currentCell;
      currentRow = obj.currentRow;
      currentColumn = obj.currentColumn;
      currentTime = obj.currentTime;

      timePerCell = obj.timePerCell;

      // precompute the X and Y values of a cells
      xMultiplier = 1.0f / columns;
      yMultiplier = 1.0f / rows;
    }

		SpriteSheetUV clone() {
      return SpriteSheetUV(rows, columns, timePerCell, cells);
    }

		GLfloat getTopLeftXUv() {
      return xMultiplier * currentColumn;
    }

		GLfloat getTopLeftYUv() {
      return yMultiplier * (currentRow + 1);
    }

		GLfloat getTopRightXUv() {
      return xMultiplier * (currentColumn + 1);
    }

		GLfloat getTopRightYUv() {
      return yMultiplier * (currentRow + 1);
    }

		GLfloat getBottomLeftXUv() {
      return xMultiplier * currentColumn;
    }

		GLfloat getBottomLeftYUv() {
      return yMultiplier * currentRow;
    }

		GLfloat getBottomRightXUv() {
      return xMultiplier * (currentColumn + 1);
    }

		GLfloat getBottomRightYUv() {
      return yMultiplier * currentRow;
    }

		/**
		 * Updates the positions to the next cell in the spritesheet
		 * Comes back to zero if the last
		 */
		void nextCell() {
      currentCell += 1;

      if (currentCell >= cells) {
        currentCell = 0;
        currentColumn = 0;
        currentRow = 0;

      }
      else {
        currentColumn += 1;

        if (currentColumn >= columns) {
          currentColumn = 0;
          currentRow += 1;
        }
      }
    }

		/**
		 * Adds a tick to the counter,
		 * automatically changes the current cell if 'currentTick >= ticksPerCell'
		 */
		void time(float delta) {
      currentTime += delta;

      if (currentTime >= timePerCell) {
        currentTime = 0;
        nextCell();
      }
    }

	};

}