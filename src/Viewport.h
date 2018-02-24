#pragma once

#include "Buffer.h"
#include "Pixel.h"

#include <vector>

using namespace std;

class Viewport
{
    public:
        // Points of floodfill
        vector<int> x;
        vector<int> y;

        // Number of points
        const unsigned int num_points = 4;

        // Size
        unsigned int width;
        unsigned int height;

        // Border color
        unsigned int border_color;

        // Border transparency
        unsigned int border_alpha;

        // Border thickness
        unsigned int border_thickness;

        // Default background color
        unsigned int background_color;

        // Center point
        int center_x;
        int center_y;

        // Constructor
        Viewport(unsigned int _width, unsigned int _height, unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness = 1, unsigned int _background_color = 0);

        // Add coordinates
        void add(unsigned int _x_min, unsigned int _y_min);

        // Set center point
        void setCenter();

        // Draw viewport
        void draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset);
};