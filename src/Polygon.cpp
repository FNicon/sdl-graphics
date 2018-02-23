#include "Polygon.h"

#include "Line.h"

using namespace std;

// Constructor
Polygon::Polygon(unsigned int _border_color, unsigned int _border_alpha, unsigned int _border_thickness, unsigned int _fill_color, unsigned int _fill_alpha, int _layer)
{
    border_color = _border_color;
    border_alpha = _border_alpha;
    border_thickness = _border_thickness;
    fill_color = _fill_color;
    fill_alpha = _fill_alpha;
    layer = _layer;

    x.clear();
    y.clear();
    num_points = 0;
}

// Add points to Polygon
void Polygon::add(double _x, double _y)
{
    x.push_back(_x);
    y.push_back(_y);
    num_points++;
}

// Draw
void Polygon::draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset)
{
    int x1, y1;
    int x2, y2;

    for(size_t idx = 0; idx < num_points; idx++)
    {
        x1 = x[idx];
        y1 = y[idx];

        x2 = x[(idx+1) % num_points];
        y2 = y[(idx+1) % num_points];

        Line line(x1, y1, x2, y2, border_color, border_alpha, border_thickness, layer);
        line.draw(_buffer, _row_offset, _col_offset);
    }
}