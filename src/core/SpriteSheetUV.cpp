#include "SpriteSheetUV.h"

#include <iostream>

namespace cge {
	SpriteSheetUV::SpriteSheetUV() {

	}

	SpriteSheetUV::SpriteSheetUV(int _rows, int _columns, float _timePerCell, int _cells) {
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

	SpriteSheetUV::SpriteSheetUV(const SpriteSheetUV & obj) {
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

	SpriteSheetUV SpriteSheetUV::clone() {
		return SpriteSheetUV(rows, columns, timePerCell, cells);
	}

	GLfloat SpriteSheetUV::getBottomLeftXUv() {
		return xMultiplier * currentColumn;
	}
	GLfloat SpriteSheetUV::getBottomLeftYUv() {
		return yMultiplier * currentRow;
	}

	GLfloat SpriteSheetUV::getBottomRightXUv() {
		return xMultiplier * (currentColumn + 1);
	}
	GLfloat SpriteSheetUV::getBottomRightYUv() {
		return yMultiplier * currentRow;
	}

	GLfloat SpriteSheetUV::getTopLeftXUv() {
		return xMultiplier * currentColumn;
	}
	GLfloat SpriteSheetUV::getTopLeftYUv() {
		return yMultiplier * (currentRow + 1);
	}

	GLfloat SpriteSheetUV::getTopRightXUv() {
		return xMultiplier * (currentColumn + 1);
	}
	GLfloat SpriteSheetUV::getTopRightYUv() {
		return yMultiplier * (currentRow + 1);
	}

	void SpriteSheetUV::nextCell() {
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

	void SpriteSheetUV::time(float delta) {
		currentTime += delta;

		if (currentTime >= timePerCell) {
			currentTime = 0;
			nextCell();
		}
	}
}