#include "Circle.h"

using namespace std;

// Constructor
Circle::Circle(int _x0, int _y0, int _r, unsigned int _color, unsigned int _alpha, int _layer)
{
    x0 = _x0;
    y0 = _y0;
    r = _r;
    color = _color;
    alpha = _alpha;
    layer = _layer;
}

// Draw circle
void Circle::draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset)
{
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y)
    {
        _buffer.set(_row_offset + x0 + x, _col_offset + y0 + y, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 + y, _col_offset + y0 + x, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 - y, _col_offset + y0 + x, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 - x, _col_offset + y0 + y, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 - x, _col_offset + y0 - y, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 - y, _col_offset + y0 - x, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 + y, _col_offset + y0 - x, Pixel(color, alpha, layer));
        _buffer.set(_row_offset + x0 + x, _col_offset + y0 - y, Pixel(color, alpha, layer));

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}
