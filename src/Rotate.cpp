#include "Rotate.h"
#include "Translate.h"

using namespace std;

// Constructor
Rotate::Rotate()
{
    num_rules = 0;
}

// Add new rotate rule using polygon's center point
void Rotate::set(double _angle, int _frame)
{
    mode.push_back(ROTATE_CENTER);
    angle.push_back(_angle);
    frame.push_back(_frame);

    num_rules++;
}

// Add new rotate rule using polygon's vertex
void Rotate::set(int _vertex_idx, double _angle, int _frame)
{
    mode.push_back(ROTATE_VERTEX);
    origin_vertex.push_back(_vertex_idx);
    angle.push_back(_angle);
    frame.push_back(_frame);

    num_rules++;
}

// Add new rotate rule using fixed-positioned point
void Rotate::set(int _origin_x, int _origin_y, double _angle, int _frame)
{
    mode.push_back(ROTATE_FIXED);
    origin_x.push_back(_origin_x);
    origin_y.push_back(_origin_y);
    angle.push_back(_angle);
    frame.push_back(_frame);

    num_rules++;
}

// Rotate polygon by counterclockwise angle relative to pivot every frame
void Rotate::transform(Polygon& _polygon, unsigned int _fps_count)
{
    // Ignore expired rules
    unsigned int total_fps = 0;
    int rule_idx = -1;

    for(size_t idx = 0; idx < num_rules; idx++)
    {
        if(frame[idx] == 0)
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

        double rad_angle;
        rad_angle = (2 * PI * angle[rule_idx])/360;

        for(size_t idx = 0; idx < num_points; idx++)
        {
            if(mode[rule_idx] == ROTATE_FIXED)
            {
                relative_x = _polygon.x[idx] - origin_x[rule_idx];
                relative_y = _polygon.y[idx] - origin_y[rule_idx];

                _polygon.x[idx] = round(relative_x * cos(rad_angle) + relative_y * sin(rad_angle)) + origin_x[rule_idx];
                _polygon.y[idx] = round(relative_x * -1 * sin(rad_angle) + relative_y * cos(rad_angle)) + origin_y[rule_idx];   
            }
            else if(mode[rule_idx] == ROTATE_VERTEX)
            {
                relative_x = _polygon.x[idx] - _polygon.x[origin_vertex[rule_idx]];
                relative_y = _polygon.y[idx] - _polygon.y[origin_vertex[rule_idx]];

                _polygon.x[idx] = round(relative_x * cos(rad_angle) + relative_y * sin(rad_angle)) + _polygon.x[origin_vertex[rule_idx]];
                _polygon.y[idx] = round(relative_x * -1 * sin(rad_angle) + relative_y * cos(rad_angle)) + _polygon.y[origin_vertex[rule_idx]];
            }
            else
            {
                relative_x = _polygon.x[idx] - _polygon.center_x;
                relative_y = _polygon.y[idx] - _polygon.center_y;
            
                _polygon.x[idx] = round(relative_x * cos(rad_angle) + relative_y * sin(rad_angle)) + _polygon.center_x;
                _polygon.y[idx] = round(relative_x * -1 * sin(rad_angle) + relative_y * cos(rad_angle)) + _polygon.center_y;
            }
        }

        if(mode[rule_idx] == ROTATE_FIXED || mode[rule_idx] == ROTATE_VERTEX) _polygon.setCenter();
    }
}