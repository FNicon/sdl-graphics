#pragma once

#include "ITransform.h"
#include <cmath>

class Rotate : public ITransform
{
    public:
        int origin_x;
        int origin_y;
        double angle;

        const double PI = acos(-1);

        // Constructor
        Rotate(int _origin_x, int _origin_y, double _angle);

        // Rotate polygon by counterclockwise angle relative to pivot every frame
        void transform(Polygon& _polygon, unsigned int _fps_count);

        // Support for center point rotation
};