#include "Translate.h"

using namespace std;

// Constructor
Translate::Translate()
{
    num_rules = 0;
}

void Translate::set(double _x_offset, double _y_offset, int _frame)
{
    x_offset.push_back(_x_offset);
    y_offset.push_back(_y_offset);
    frame.push_back(_frame);

    num_rules++;
}

// Translate shape by offset every frame
void Translate::transform(IShape* _shape, unsigned int _fps_count)
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
        size_t num_points = _shape->num_points;

        if(_shape->num_points == 0) // circle
        {
            Circle* _circle = static_cast<Circle*>(_shape);

            _circle->x0 += x_offset[rule_idx];
            _circle->y0 += y_offset[rule_idx];
            _circle->setCenter();
        }
        else // polygon
        {
            Polygon* _polygon = static_cast<Polygon*>(_shape);

            for(size_t idx = 0; idx < num_points; idx++)
            {
                _polygon->x[idx] += x_offset[rule_idx];
                _polygon->y[idx] += y_offset[rule_idx];
            }

            _polygon->setCenter();
        }
    }
}

void Translate::transform(Viewport& _viewport, unsigned int _fps_count)
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
        size_t num_points = _viewport.num_points;

        for(size_t idx = 0; idx < num_points; idx++)
        {
            _viewport.x[idx] += x_offset[rule_idx];
            _viewport.y[idx] += y_offset[rule_idx];
        }

        _viewport.setCenter();
    }
}