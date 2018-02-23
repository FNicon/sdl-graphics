#pragma once

#include "ITransform.h"
#include <cmath>

class Rotate : public ITransform
{
    private:
        // Constants
        const int ROTATE_FIXED = 0; // fixed-positioned point
        const int ROTATE_VERTEX = 1; // polygon's vertex
        const int ROTATE_CENTER = 2; // polygon's center point

        const double PI = acos(-1);

    public:
        // Rotate mode
        vector<int> mode;

        // Rotate by fix-positioned point
        vector<int> origin_x;
        vector<int> origin_y;

        // Rotate by polygon's vertex
        vector<int> origin_vertex;

        // Angle (degrees)
        vector<double> angle;

        // Rotate duration in number of frames, -1 = forever
        vector<int> frame;

        // Number of rules
        size_t num_rules;

        // Constructor
        Rotate();

        // Add new rotate rule
        void set(double _angle, int _frame = -1); // using polygon's center point
        void set(int _vertex_idx, double _angle, int _frame = -1); // using polygon's vertex
        void set(int _origin_x, int _origin_y, double _angle, int _frame = -1); // using fixed-positioned point

        // Rotate polygon by counterclockwise angle relative to pivot every frame
        void transform(Polygon& _polygon, unsigned int _fps_count);
};