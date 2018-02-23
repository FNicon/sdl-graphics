#pragma once

#include "ITransform.h"

class Translate : public ITransform
{
    public:
        double x_offset;
        double y_offset;

        // Constructor
        Translate(double _x_offset, double _y_offset);

        // Translate polygon by offset every frame
        void transform(Polygon& _polygon, unsigned int _fps_count);
};