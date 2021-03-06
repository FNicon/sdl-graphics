#include "Viewport.h"
#include "Line.h"

#include <cmath>

using namespace std;

// Constructor
Viewport::Viewport(unsigned int _width, unsigned int _height, unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness, unsigned int _background_color)
{
    width = _width;
    height = _height;
    border_color = _border_color;
    border_alpha = _border_alpha;
    border_thickness = _border_thickness;
    background_color = _background_color;
    layer = 100;
}

// Add coordinates
void Viewport::add(unsigned int x_min, unsigned int y_min)
{
    x.push_back(x_min - border_thickness); y.push_back(y_min - border_thickness);
    x.push_back(x_min + width); y.push_back(y_min - border_thickness);
    x.push_back(x_min + width); y.push_back(y_min + height);
    x.push_back(x_min - border_thickness); y.push_back(y_min + height);
}

// Set center point
void Viewport::setCenter()
{
    double x_min, x_max, y_min, y_max;
    x_min = x_max = x[0];
    y_min = y_max = y[0];

    for(size_t idx = 1; idx < num_points; idx++)
    {
        if(x[idx] < x_min) x_min = x[idx];
        if(x[idx] > x_max) x_max = x[idx];
        if(y[idx] < y_min) y_min = y[idx];
        if(y[idx] > y_max) y_max = y[idx];
    }

    center_x = round((x_min + x_max) / 2);
    center_y = round((y_min + y_max) / 2);
}

// Draw viewport
void Viewport::draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset)
{
    int x1, y1;
    int x2, y2;

    for(unsigned int idx = 0; idx < num_points; idx++)
    {
        x1 = x[idx];
        y1 = y[idx];

        x2 = x[(idx+1) % num_points];
        y2 = y[(idx+1) % num_points];

        Line line(x1, y1, x2, y2, border_color, border_alpha, border_thickness);
        line.draw(_buffer, _row_offset, _col_offset);
    }
}