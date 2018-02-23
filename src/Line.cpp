#include "Line.h"

using namespace std;

// Constructor
Line::Line(int _x1, int _y1, int _x2, int _y2, unsigned int _color, unsigned int _alpha, unsigned int _thickness, int _layer)
{
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
    color = _color;
    alpha = _alpha;
    thickness = _thickness;
    layer = _layer;
}

// Draw line
void Line::draw(Buffer<Pixel>& _buffer, int _row_offset, int _col_offset)
{
    if(abs(y2 - y1) < abs(x2 - x1)) drawX(_buffer, _row_offset, _col_offset); // If number of pixels on X axis >= Y axis.
    else drawY(_buffer, _row_offset, _col_offset); // If number of pixels on X axis < Y axis.
}

// Draw by coloring pixels for every X
void Line::drawX(Buffer<Pixel>& _buffer, int _row_offset, int _col_offset)
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    int p = 2 * dy - dx;

    const int const1 = 2 * dy;
    const int const2 = 2 * (dy - dx);

    int x, x_end, y, y_end;
    int sign;
    unsigned int world_row, world_col;

    if(x1 > x2)
    {
        x = x2;
        y = y2;
        x_end = x1;
        y_end = y1;
    }
    else
    {
        x = x1;
        y = y1;
        x_end = x2;
        y_end = y2;
    }

    if(y_end < y) sign = -1;
    else if(y_end > y) sign = 1;
    else sign = 0;

    for(unsigned int t = 0; t < thickness; t++)
    {
        world_row = y + t + _row_offset;
        world_col = x + _col_offset;
        _buffer.set(world_row, world_col, Pixel(color, alpha, layer));
    }

    while(x < x_end)
    {
        x++;

        if(p < 0) p += const1;
        else
        {
            y = y + sign;
            p += const2;
        }

        for(unsigned int t = 0; t < thickness; t++)
        {
            world_row = y + t + _row_offset;
            world_col = x + _col_offset;
            _buffer.set(world_row, world_col, Pixel(color, alpha, layer));
        }    
    }
}

// Draw by coloring pixels for every Y 
void Line::drawY(Buffer<Pixel>& _buffer, int _row_offset, int _col_offset)
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);

    int p = 2 * dx - dy;

    const int const1 = 2 * dx;
    const int const2 = 2 * (dx - dy);

    int x, x_end, y, y_end;
    int sign;
    unsigned int world_row, world_col;

    if(y1 > y2)
    {
        x = x2;
        y = y2;
        x_end = x1;
        y_end = y1;
    }
    else
    {
        x = x1;
        y = y1;
        x_end = x2;
        y_end = y2;
    }

    if(x_end < x) sign = -1;
    else if(x_end > x) sign = 1;
    else sign = 0;

    for(unsigned int t = 0; t < thickness; t++)
    {
        world_row = y + _row_offset;
        world_col = x + t + _col_offset;
        _buffer.set(world_row, world_col, Pixel(color, alpha, layer));
    }

    while(y < y_end)
    {
        y++;

        if(p < 0) p += const1;
        else
        {
            x = x + sign;
            p += const2;
        }

        for(unsigned int t = 0; t < thickness; t++)
        {
            world_row = y + _row_offset;
            world_col = x + t + _col_offset;
            _buffer.set(world_row, world_col, Pixel(color, alpha, layer));
        }
    }
}