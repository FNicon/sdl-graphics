#pragma once

#include "Polygon.h"
#include "Viewport.h"

class ITransform
{
    public:
        // Transform method
        virtual void transform(Polygon& _polygon, unsigned int _fps_count) = 0;
        virtual void transform(Viewport& _viewport, unsigned int _fps_count) = 0;
};