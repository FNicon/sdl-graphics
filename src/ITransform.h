#pragma once

#include "Polygon.h"

class ITransform
{
    public:
        // Transform method
        virtual void transform(Polygon& _polygon, unsigned int _fps_count) = 0;
};