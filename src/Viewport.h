#pragma once

using namespace std;

class Viewport
{
    public:
        // Size
        unsigned int width;
        unsigned int height;

        // Border color
        unsigned int border_color;

        // Border transparency
        unsigned int border_alpha;

        // Border thickness
        unsigned int border_thickness;

        // Constructor
        Viewport(unsigned int _width, unsigned int _height, unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness = 1);
};