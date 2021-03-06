#include "Polygon.h"
#include "Line.h"

#include <cmath>
#include <queue>
#include <utility>

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

// Set center point
void Polygon::setCenter()
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

// Fill
void Polygon::fill(Buffer<Pixel>& _buffer, unsigned int _row_offset, unsigned int _col_offset)
{
    Pixel polygon_pix(fill_color, fill_alpha, layer);
    queue< pair< int,int > > q;

    int delta_row[4] = {0, 1, 0, -1};
    int delta_col[4] = {1, 0, -1, 0};

    q.push(make_pair(center_y, center_x));
    _buffer.set(center_y + _row_offset, center_x + _col_offset, polygon_pix);

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