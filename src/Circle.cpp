#include "Circle.h"

#include <queue>
#include <utility>

using namespace std;

// Constructor
Circle::Circle(int _x0, int _y0, int _r, unsigned int _border_color, unsigned int _border_alpha, unsigned int _fill_color, unsigned int _fill_alpha, int _layer)
{
    x0 = _x0;
    y0 = _y0;
    r = _r;
    border_color = _border_color;
    border_alpha = _border_alpha;
    fill_color = _fill_color;
    fill_alpha = _fill_alpha;
    layer = _layer;

    num_points = 0;
}

// Set center point
void Circle::setCenter() {}

// Draw
void Circle::draw(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset)
{
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y)
    {
        _buffer.set(_row_offset + x0 + x, _col_offset + y0 + y, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 + y, _col_offset + y0 + x, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 - y, _col_offset + y0 + x, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 - x, _col_offset + y0 + y, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 - x, _col_offset + y0 - y, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 - y, _col_offset + y0 - x, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 + y, _col_offset + y0 - x, Pixel(border_color, border_alpha, layer));
        _buffer.set(_row_offset + x0 + x, _col_offset + y0 - y, Pixel(border_color, border_alpha, layer));

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

// Fill
void Circle::fill(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset)
{
    
    Pixel polygon_pix(fill_color, fill_alpha, layer);
    queue< pair< int,int > > q;

    int delta_row[4] = {0, 1, 0, -1};
    int delta_col[4] = {1, 0, -1, 0};

    q.push(make_pair(y0, x0));
    _buffer.set(y0 + _row_offset, x0 + _col_offset, polygon_pix);

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for(int k=0;k<4;k++)
        {
            int next_row = row + delta_row[k];
            int next_col = col + delta_col[k];

            Pixel buffer_pix = _buffer.get(next_row + _row_offset, next_col + _col_offset);
            
            if(buffer_pix.layer != layer)
            {
                _buffer.set(next_row + _row_offset, next_col + _col_offset, polygon_pix);
                q.push(make_pair(next_row, next_col));
            }
        }
    }
    
}