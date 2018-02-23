#pragma once

#include "ITransform.h"

class Scale : public ITransform
{
    public:
        int origin_x;
        int origin_y;
        double multiplier;

        // Constructor
        Scale(int _origin_x, int _origin_y, double _multiplier);

        // Scale polygon by multiplier relative to origin every frame
        void transform(Polygon& _polygon);
};