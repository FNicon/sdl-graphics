#include "Viewport.h"

using namespace std;

// Constructor
Viewport::Viewport(unsigned int _width, unsigned int _height, unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness)
{
    width = _width;
    height = _height;
    border_color = _border_color;
    border_alpha = _border_alpha;
    border_thickness = _border_thickness;
}