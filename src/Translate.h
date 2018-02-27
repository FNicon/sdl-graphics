#pragma once

#include "ITransform.h"

#include <vector>

class Translate : public ITransform
{
    public:
        // Translate offsets
        vector<double> x_offset;
        vector<double> y_offset;

        // Translate duration in number of frames, 0 = forever
        vector<int> frame;

        // Number of rules
        size_t num_rules;

        // Constructor
        Translate();

        // Add new translate rule
        void set(double _x_offset, double _y_offset, int _frame = -1);

        // Translate shape by offset every frame
        void transform(IShape* _shape, unsigned int _fps_count);
        void transform(Viewport& _viewport, unsigned int _fps_count);
};