#include "World.h"
#include "RawPixel.h"

#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

/* Private access */

// Comparison function for sorting
bool World::compare(const pair< IShape*, vector<ITransform*>* >& p1, const pair< IShape*, vector<ITransform*>* >& p2)
{
    return p1.first->layer < p2.first->layer;
}

// Clip, draw and fill shapes to buffer, draw viewport
void World::draw()
{
    for(size_t idx = 0; idx < num_shapes; idx++)
    {
        /*
        int current_layer = shapes[idx].first->layer;
        
        if(viewport != nullptr)
        {
            int prev_center_x, prev_center_y, new_center_x, new_center_y;
            Polygon* polygon, Circle* circle;

            if(shapes[idx].first->num_points == 0)
            {
                circle = static_cast<Circle*>(shapes[idx].first);
                prev_center_x = circle->x0;
                prev_center_y = circle->y0;
            }
            else
            {
                polygon = static_cast<Polygon*>(shapes[idx].first);
                prev_center_x = polygon->center_x;
                prev_center_y  = polygon->center_y;
            }

            unsigned int viewport_x_max, viewport_x_min, viewport_y_max, viewport_y_min;

            viewport_x_min = SDL_origin_col + viewport->x[0];
            viewport_y_min = SDL_origin_row + viewport->y[0];
            viewport_x_max = SDL_origin_col + viewport->x[2];
            viewport_y_max = SDL_origin_row + viewport->y[2];
            viewport_thickness = viewport->thickness;

            // Determine new floodfill point

            if(prev_center_x >= viewport_x_min + viewport_thickness && prev_center_x < viewport_x_max && prev_center_y >= viewport_y_min + viewport_thickness && prev_center_y < viewport_y_max)
            {
                new_center_x = prev_center_x;
                new_center_y = prev_center_y;
            }
            else if(prev_center_x >= viewport_x_min && prev_center_x < viewport_x_min + viewport_thickness && prev_center_y >= viewport_y_min + viewport_thickness && prev_center_y < viewport_y_max)
            {
                new_center_x = viewport_x_min + viewport_thickness;
                new_center_y = prev_center_y;
            }
            else if(prev_center_x >= viewport_x_max && prev_center_x < viewport_x_max + viewport_thickness && prev_center_y >= viewport_y_min + viewport_thickness && prev_center_y < viewport_y_max)
            {
                new_center_x = viewport_x_max - 1;
                new_center_y = prev_center_y;
            }
            else if(prev_center_x >= viewport_x_min + viewport_thickness && prev_center_x < viewport_x_max && prev_center_y >= viewport_y_min && prev_center_y < viewport_y_max + viewport_thickness)
            {
                new_center_x = prev_center_x;
                new_center_y = viewport_y_min + viewport_thickness;
            }
            else if(prev_center_x >= viewport_x_min + viewport_thickness && prev_center_x < viewport_x_max && prev_center_y >= viewport_y_max && prev_center_y < viewport_y_max + viewport_thickness)
            {
                new_center_x = prev_center_x;
                new_center_y = viewport_y_max - 1;
            }

            viewport->layer = current_layer;
            viewport->draw(buffer, SDL_origin_row, SDL_origin_col);
        }
        */
        // Draw polygon
        shapes[idx].first->draw(buffer, SDL_origin_row, SDL_origin_col);
        shapes[idx].first->fill(buffer, SDL_origin_row, SDL_origin_col);
    }

    // Draw viewport
    if(viewport != nullptr)
    {
        //viewport->layer = 100;
        viewport->draw(buffer, SDL_origin_row, SDL_origin_col);
    }
}

// Transform all shapes in World
void World::transform()
{
    for(size_t idx = 0; idx < num_shapes; idx++)
    {
        if(shapes[idx].second != nullptr)
        {
            size_t transformations = shapes[idx].second->size();

            for(size_t t = 0; t < transformations; t++)
            {
                (*(shapes[idx].second))[t]->transform(shapes[idx].first, fps_count);
            }
        }
    }

    if(viewport != nullptr) 
    {
        for(size_t idx = 0; idx < num_viewport_trans; idx++) (*(viewport_trans))[idx]->transform(*viewport, fps_count);
    }
}

// Flush World's buffer to SDL's buffer
void World::flush()
{
    size_t SDL_width = display->width;
    size_t SDL_height = display->height;

    unsigned int world_row, world_col, hex;
    Pixel pix, viewport_backgound(background_color, 0, -99);

    unsigned int viewport_x_max, viewport_x_min, viewport_y_max, viewport_y_min;

    if(viewport != nullptr)
    {
        viewport_x_min = SDL_origin_col + viewport->x[0];
        viewport_y_min = SDL_origin_row + viewport->y[0];
        viewport_x_max = SDL_origin_col + viewport->x[2];
        viewport_y_max = SDL_origin_row + viewport->y[2];
    }

    for(size_t SDL_row = 0; SDL_row < SDL_height; SDL_row++)
    {
        for(size_t SDL_col = 0; SDL_col < SDL_width; SDL_col++)
        {
            world_row = SDL_origin_row + (unsigned int) SDL_row;
            world_col = SDL_origin_col + (unsigned int) SDL_col;

            if(viewport != nullptr)
            {
                // Inside viewport
                if(world_row >= viewport_y_min && world_row <= viewport_y_max && world_col >= viewport_x_min && world_col <= viewport_x_max)
                {
                    pix = buffer.get(world_row, world_col);
                    if(pix == viewport_backgound) pix = Pixel(viewport->background_color, 0, -99);

                    hex = (pix.r << 24) + (pix.g << 16) + (pix.b << 8) + pix.a;
                    display->set(SDL_row, SDL_col, RawPixel(hex));
                }
                else
                {
                    hex = background_color << 8;
                    display->set(SDL_row, SDL_col, RawPixel(hex));
                }
            }
            else
            {
                pix = buffer.get(world_row, world_col);
                hex = (pix.r << 24) + (pix.g << 16) + (pix.b << 8) + pix.a;
                display->set(SDL_row, SDL_col, RawPixel(hex));
            }
        }
    }
}

// Reset World's buffer
void World::reset()
{
    unsigned int hex;
    unsigned int viewport_x_max, viewport_x_min, viewport_y_max, viewport_y_min;

    if(viewport != nullptr)
    {
        viewport_x_min = SDL_origin_col + viewport->x[0];
        viewport_y_min = SDL_origin_row + viewport->y[0];
        viewport_x_max = SDL_origin_col + viewport->x[2];
        viewport_y_max = SDL_origin_row + viewport->y[2];
    }

    for(size_t row = 0; row < height; row++)
    {
        for(size_t col = 0; col < width; col++)
        {
            if(viewport != nullptr)
            {
                // Inside viewport
                if(row >= viewport_y_min && row <= viewport_y_max && col >= viewport_x_min && col <= viewport_x_max)
                {
                    hex = background_color;
                    buffer.set(row, col, Pixel(hex, 0, -99));
                }
                // Outside viewport
                else
                {
                    hex = background_color;
                    buffer.set(row, col, Pixel(hex, 0, -100));
                }
            }
            else
            {
                hex = background_color;
                buffer.set(row, col, Pixel(hex, 0, -100));
            }
        }
    }
}

/* Public access */

// Constructors
World::World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col, unsigned int _background_color) : buffer(_width, _height)
{
    width = _width;
    height = _height;
    SDL_origin_row = _SDL_origin_row;
    SDL_origin_col = _SDL_origin_col;
    background_color = _background_color;

    num_shapes = 0;
    num_viewport_trans = 0;
    fps_count = 0;
}

// Getter, coordinate relative to SDL display origin point
Pixel World::get(size_t _row, size_t _col)
{
    unsigned int world_row = _row + SDL_origin_row;
    unsigned int world_col = _col + SDL_origin_col;

    return buffer.get(world_row, world_col);
}

// Setter, coordinate relative to SDL display origin point
void World::set(size_t _row, size_t _col, Pixel _pixel)
{
    unsigned int world_row = _row + SDL_origin_row;
    unsigned int world_col = _col + SDL_origin_col;

    buffer.set(world_row, world_col, _pixel);
}

// Reset fps_count, animation will start from beginning
void World::resetFPSCount(unsigned int _elapsed_frames, int _fps_reset)
{
    elapsed_frames = _elapsed_frames;
    fps_reset = _fps_reset;
}

// Add a shape to World
void World::addShape(IShape* _shape, vector<ITransform*>* _transform)
{
    shapes.push_back(make_pair(_shape, _transform));
    num_shapes++;
}

// Add viewport transformations
void World::addViewportTrans(vector<ITransform*>* _transform)
{
    viewport_trans = _transform;
    num_viewport_trans = _transform->size();
}

// Render
void World::render(unsigned int fps)
{
    if(!is_sorted(shapes.begin(), shapes.end(), compare)) sort(shapes.begin(), shapes.end(), compare);

    if(fps != 0)
    {
        while(true)
        {
            reset();
            transform();
            draw();
            flush();
            display->render();

            fps_count++;

            if(fps_count == elapsed_frames && fps_reset != 0)
            {
                if(fps_reset != -1) fps_reset--;
                fps_count = 0;
            }

            this_thread::sleep_for(chrono::milliseconds(1000 / fps));
        }
    }
    else
    {
        reset();
        transform();
        draw();
        flush();
        display->render();
    }
}