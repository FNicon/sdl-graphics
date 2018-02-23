#pragma once

#include "Buffer.h"
#include "Pixel.h"

class Line
{
    public:
        // Coordinate
        int x1, y1;
        int x2, y2;

        // Color
        unsigned int color;

        // Transparency
        unsigned int alpha;

        // Layer
        int layer;

        // Thickness
        unsigned int thickness;

        // Constructor
        Line(int _x1, int _y1, int _x2, int _y2, unsigned int _color, unsigned int _alpha, unsigned int _thickness = 1, int _layer = 0);

        // Draw line
        void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);

        void drawX(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset); // Draw by coloring pixels for every X
        void drawY(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset); // Draw by coloring pixels for every Y
};