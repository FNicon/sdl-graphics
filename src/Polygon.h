#pragma once

#include <vector>

#include "Buffer.h"
#include "Pixel.h"

class Polygon
{
    public:
        // Points of polygon
        vector<double> x; // x coordinates
        vector<double> y; // y coordinates

        // Number of points
        size_t num_points;

        // Color
        unsigned int border_color;
        unsigned int fill_color;

        // Transparency
        unsigned int border_alpha;
        unsigned int fill_alpha;

        // Border thickness
        unsigned int border_thickness;

        // Layer
        int layer;

        // Center point
        int center_x;
        int center_y;

        // Constructor
        Polygon(unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness, unsigned int _fill_color, unsigned int _fill_alpha, int _layer = 0);

        // Add points to Polygon
        void add(double _x, double _y);

        // Set center point
        void setCenter();

        // Draw
        void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);
};