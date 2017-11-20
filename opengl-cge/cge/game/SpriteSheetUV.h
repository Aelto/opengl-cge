#pragma once

#include <GL\glew.h>

#include "../core/Texture.h"

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

        

        SpriteSheetUV(int _rows, int _columns, float _timePerCell, int _cells = -1);
				
        // copy constructor
        SpriteSheetUV(const SpriteSheetUV & obj);

        SpriteSheetUV clone();

        GLfloat getTopLeftXUv();
        GLfloat getTopLeftYUv();

        GLfloat getTopRightXUv();
        GLfloat getTopRightYUv();

        GLfloat getBottomLeftXUv();
        GLfloat getBottomLeftYUv();

        GLfloat getBottomRightXUv();
        GLfloat getBottomRightYUv();

        /**
         * Updates the positions to the next cell in the spritesheet
         * Comes back to zero if the last
         */
        void nextCell();

        /**
         * Adds a tick to the counter, 
         * automatically changes the current cell if 'currentTick >= ticksPerCell'
         */
        void time(float delta);

    };

}