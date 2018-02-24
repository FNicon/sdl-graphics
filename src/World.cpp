#include "World.h"
#include "RawPixel.h"

#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

/* Private access */

// Comparison function for sorting
bool World::compare(const pair< Polygon*, vector<ITransform*>* >& p1, const pair< Polygon*, vector<ITransform*>* >& p2)
{
    return p1.first->layer < p2.first->layer;
}

// Draw and fill polygon to buffer, draw viewport
void World::draw()
{
    for(size_t idx = 0; idx < num_polygon; idx++) 
    {
        polygons[idx].first->draw(buffer, SDL_origin_row, SDL_origin_col);
        polygons[idx].first->fill(buffer, SDL_origin_row, SDL_origin_col);
    }

    viewport->draw(buffer, SDL_origin_row, SDL_origin_col);
}

// Transform all Polygons in World
void World::transform()
{
    for(size_t idx = 0; idx < num_polygon; idx++)
    {
        if(polygons[idx].second != nullptr)
        {
            size_t transformations = polygons[idx].second->size();

            for(size_t t = 0; t < transformations; t++)
            {
                (*(polygons[idx].second))[t]->transform(*(polygons[idx].first), fps_count);
            }
        }
    }

    for(size_t idx = 0; idx < num_viewport_trans; idx++)
    {
        (*(viewport_trans))[idx]->transform(*viewport, fps_count);
    }
}

// Flush World's buffer to SDL's buffer
void World::flush()
{
    size_t SDL_width = display->width;
    size_t SDL_height = display->height;

    unsigned int world_row, world_col, hex;
    Pixel pix;

    unsigned int viewport_x_max, viewport_x_min, viewport_y_max, viewport_y_min;

    if(viewport != nullptr)
    {
        viewport_x_min = SDL_origin_col + viewport->x[0];
        viewport_y_min = SDL_origin_row + viewport->y[0];
        viewport_x_max = SDL_origin_col + viewport->x[2];
        viewport_y_max = SDL_origin_row + viewport->x[2];
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
                    hex = (pix.r << 24) + (pix.g << 16) + (pix.b << 8) + pix.a;
                    display->set(SDL_row, SDL_col, RawPixel(hex));
                }
                else
                {
                    hex = (background_color << 8);
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
        viewport_y_max = SDL_origin_row + viewport->x[2];
    }

    for(size_t row = 0; row < height; row++)
    {
        for(size_t col = 0; col < width; col++)
        {
            if(viewport != nullptr)
            {
                // Inside viewport
                if(row > viewport_y_min && row < viewport_y_max && col > viewport_x_min && col < viewport_x_max)
                {
                    hex = (viewport->background_color << 8);
                    buffer.set(row, col, Pixel(hex, 0, -100));
                }
                // Outside viewport
                else
                {
                    hex = (background_color << 8);
                    buffer.set(row, col, Pixel(hex, 0, -100));
                }
            }
            else
            {
                buffer.set(row, col, Pixel(background_color, 0, -100));
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

    num_polygon = 0;
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
void World::reset_fps_count(unsigned int _elapsed_frames, int _fps_reset)
{
    elapsed_frames = _elapsed_frames;
    fps_reset = _fps_reset;
}

// Add a polygon to World
void World::addPolygon(Polygon* _polygon, vector<ITransform*>* _transform)
{
    polygons.push_back(make_pair(_polygon, _transform));
    num_polygon++;
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
    sort(polygons.begin(), polygons.end(), compare);

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