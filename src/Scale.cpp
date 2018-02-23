#include "Scale.h"

using namespace std;

// Constructor
Scale::Scale()
{
    num_rules = 0;
}

// Add new scale rule using polygon's center point
void Scale::set(double _multiplier, int _frame)
{
    mode.push_back(SCALE_CENTER);
    multiplier.push_back(_multiplier);
    frame.push_back(_frame);

    num_rules++;
}

// Add new scale rule using polygon's vertex
void Scale::set(int _vertex_idx, double _multiplier, int _frame)
{
    mode.push_back(SCALE_VERTEX);
    origin_vertex.push_back(_vertex_idx);
    multiplier.push_back(_multiplier);
    frame.push_back(_frame);

    num_rules++;
}

// Add new scale rule using fixed-positioned point
void Scale::set(int _origin_x, int _origin_y, double _multiplier, int _frame)
{
    mode.push_back(SCALE_FIXED);
    origin_x.push_back(_origin_x);
    origin_y.push_back(_origin_y);
    multiplier.push_back(_multiplier);
    frame.push_back(_frame);

    num_rules++;
}

// Scale polygon by multiplier relative to origin every frame
void Scale::transform(Polygon& _polygon, unsigned int _fps_count)
{
    // Ignore expired rules
    unsigned int total_fps = 0;
    int rule_idx = -1;

    for(size_t idx = 0; idx < num_rules; idx++)
    {
        if(frame[idx] == -1)
        {
            rule_idx = idx;
            break;
        }
        else
        {
            total_fps += frame[idx];
            
            if(total_fps > _fps_count)
            {
                rule_idx = idx;
                break;
            }
        }
    }

    // Apply valid rule if any
    if(rule_idx != -1)
    {
        size_t num_points = _polygon.num_points;
        int relative_x, relative_y;

        for(size_t idx = 0; idx < num_points; idx++)
        {
            if(mode[rule_idx] == SCALE_FIXED)
            {
                relative_x = _polygon.x[idx] - origin_x[rule_idx];
                relative_y = _polygon.y[idx] - origin_y[rule_idx];

                _polygon.x[idx] = relative_x * multiplier[rule_idx] + origin_x[rule_idx];
                _polygon.y[idx] = relative_y * multiplier[rule_idx] + origin_y[rule_idx];
            }
            else if(mode[rule_idx] == SCALE_VERTEX)
            {
                relative_x = _polygon.x[idx] - _polygon.x[origin_vertex[rule_idx]];
                relative_y = _polygon.y[idx] - _polygon.y[origin_vertex[rule_idx]];

                _polygon.x[idx] = relative_x * multiplier[rule_idx] + _polygon.x[origin_vertex[rule_idx]];
                _polygon.y[idx] = relative_y * multiplier[rule_idx] + _polygon.y[origin_vertex[rule_idx]];
            }
            else
            {
                relative_x = _polygon.x[idx] - _polygon.center_x;
                relative_y = _polygon.y[idx] - _polygon.center_y;

                _polygon.x[idx] = relative_x * multiplier[rule_idx] + _polygon.center_x;
                _polygon.y[idx] = relative_y * multiplier[rule_idx] + _polygon.center_y;
            }
        }

        if(mode[rule_idx] == SCALE_FIXED || mode[rule_idx] == SCALE_VERTEX) _polygon.setCenter();
    }
}