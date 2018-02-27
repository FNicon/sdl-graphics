#pragma once

#include "IShape.h"

class Circle : public IShape
{
    public:
        int x0, y0; // Center point
        int r; // Radius

        // Constructor
        Circle(int _x0, int _y0, int _r, unsigned int _border_color, unsigned int _border_alpha, unsigned int _fill_color, unsigned int _fill_alpha, int _layer = 0);

        // Set center point
        void setCenter();

        // Draw
        void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);

        // Fill
        void fill(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);
};