#pragma once

#include "Polygon.h"
#include "Circle.h"
#include "Viewport.h"

class ITransform
{
    public:
        // Transform method
        virtual void transform(IShape* _shape, unsigned int _fps_count) = 0;
        virtual void transform(Viewport& _viewport, unsigned int _fps_count) = 0;
};