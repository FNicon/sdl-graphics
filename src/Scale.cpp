#include "Scale.h"

using namespace std;

// Constructor
Scale::Scale(int _origin_x, int _origin_y, double _multiplier)
{
    origin_x = _origin_x;
    origin_y = _origin_y;
    multiplier = _multiplier;
}

// Scale polygon by multiplier relative to origin every frame
void Scale::transform(Polygon& _polygon)
{
    size_t num_points = _polygon.num_points;
    int relative_x, relative_y;

    for(size_t idx = 0; idx < num_points; idx++)
    {
        relative_x = _polygon.x[idx] - origin_x;
        relative_y = _polygon.y[idx] - origin_y;

        _polygon.x[idx] = relative_x * multiplier + origin_x;
        _polygon.y[idx] = relative_y * multiplier + origin_y;
    }
}