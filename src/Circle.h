#pragma once

#include "Buffer.h"
#include "Pixel.h"

class Circle
{
    public:
        // Coordinate
        int x0, y0;
        int r;

        // Color
        unsigned int color;

        // Transparency
        unsigned int alpha;

        // Layer
        int layer;

        // Constructor
        Circle(int _x0, int _y0, int _r, unsigned int _color, unsigned int _alpha, int _layer = 0);

        // Draw circle
        void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);
};
