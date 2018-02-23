#include "Translate.h"

using namespace std;

// Constructor
Translate::Translate(double _x_offset, double _y_offset)
{
    x_offset = _x_offset;
    y_offset = _y_offset;
}

// Translate polygon by offset every frame
void Translate::transform(Polygon& _polygon)
{
    size_t num_points = _polygon.num_points;

    for(size_t idx = 0; idx < num_points; idx++)
    {
        _polygon.x[idx] += x_offset;
        _polygon.y[idx] += y_offset;
    }
}