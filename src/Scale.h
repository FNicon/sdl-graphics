#pragma once

#include "ITransform.h"

#include <vector>

class Scale : public ITransform
{
    private:
        // Constants
        const int SCALE_FIXED = 0; // fixed-positioned point
        const int SCALE_VERTEX = 1; // polygon's vertex
        const int SCALE_CENTER = 2; // polygon's center point

    public:
        // Scale mode
        vector<int> mode;

        // Scale by fix-positioned point
        vector<int> origin_x;
        vector<int> origin_y;

        // Scale by polygon's vertex
        vector<int> origin_vertex;

        // Multiplier
        vector<double> multiplier;

        // Scale duration in number of frames, 0 = forever
        vector<int> frame;

        // Number of rules
        size_t num_rules;

        // Constructor
        Scale();

        // Add new scale rule
        void set(double _multiplier, int _frame = -1); // using polygon's center point
        void set(int _vertex_idx, double _multiplier, int _frame = -1); // using polygon's vertex
        void set(int _origin_x, int _origin_y, double _multiplier, int _frame = -1); // using fixed-positioned point

        // Scale polygon by multiplier relative to origin every frame
        void transform(Polygon& _polygon, unsigned int _fps_count);
        void transform(Viewport& _viewport, unsigned int _fps_count);
};