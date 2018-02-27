#pragma once

#include "IShape.h"

#include <vector>

class Polygon : public IShape
{
    public:
        // Points of polygon
        vector<double> x; // x coordinates
        vector<double> y; // y coordinates

        // Center point
        int center_x;
        int center_y;

        // Border thickness
        unsigned int border_thickness;

        // Constructor
        Polygon(unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness, unsigned int _fill_color, unsigned int _fill_alpha, int _layer = 0);

        // Add points to Polygon
        void add(double _x, double _y);

        // Set center point
        void setCenter();

        // Draw
        void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);

        // Fill
        void fill(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);
};