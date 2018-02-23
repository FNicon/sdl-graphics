#include "Rotate.h"

using namespace std;

// Constructor
Rotate::Rotate(int _origin_x, int _origin_y, double _angle)
{
    origin_x = _origin_x;
    origin_y = _origin_y;
    angle = _angle;
}

// Rotate polygon by counterclockwise angle relative to pivot every frame
void Rotate::transform(Polygon& _polygon, unsigned int _fps_count)
{
    size_t num_points = _polygon.num_points;
    int relative_x, relative_y;
    double rad_angle;

    rad_angle = (2 * PI * angle)/360;

    for(size_t idx = 0; idx < num_points; idx++)
    {
        relative_x = _polygon.x[idx] - origin_x;
        relative_y = _polygon.y[idx] - origin_y;

        _polygon.x[idx] = round(relative_x * cos(rad_angle) + relative_y * sin(rad_angle)) + origin_x;
        _polygon.y[idx] = round(relative_x * -1 * sin(rad_angle) + relative_y * cos(rad_angle)) + origin_y;
    }
}