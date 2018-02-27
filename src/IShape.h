#pragma once

#include "Buffer.h"
#include "Pixel.h"

class IShape
{
    public:
        // Number of points
        size_t num_points;

        // Color
        unsigned int border_color;
        unsigned int fill_color;

        // Transparency
        unsigned int border_alpha;
        unsigned int fill_alpha;

        // Layer
        int layer;

        virtual void setCenter() = 0; // Set center method
        virtual void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset) = 0; // Draw method
        virtual void fill(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset) = 0; // Fill method
};