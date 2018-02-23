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

// Draw polygon to buffer
void World::draw()
{
    for(size_t idx = 0; idx < num_polygon; idx++) polygons[idx].first->draw(buffer, SDL_origin_row, SDL_origin_col);
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
}

// Flush World's buffer to SDL's buffer
void World::flush()
{
    size_t SDL_width = display->width;
    size_t SDL_height = display->height;

    Pixel background(0, 0, -100);
    Pixel pix;

    unsigned int world_row, world_col, hex;
    unsigned int world_viewport_row, world_viewport_col;

    unsigned int viewport_x_max, viewport_x_min, viewport_y_max, viewport_y_min;
    size_t viewport_width, viewport_height;
    unsigned int viewport_thickness;

    if(viewport != nullptr)
    {
        size_t viewport_width = viewport->width;
        size_t viewport_height = viewport->height;
        unsigned int viewport_thickness = viewport->border_thickness;

        world_viewport_row = SDL_origin_row + viewport_row;
        world_viewport_col = SDL_origin_col + viewport_col;

        viewport_x_min = world_viewport_col - viewport_thickness;
        viewport_y_min = world_viewport_row - viewport_thickness;
        viewport_x_max = world_viewport_col + viewport_width;
        viewport_y_max = world_viewport_row + viewport_height;
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
                if(world_row > viewport_y_min && world_row < viewport_y_max && world_col > viewport_x_min && world_col < viewport_x_max)
                {
                    pix = buffer.get(world_row, world_col);

                    hex = (pix.r << 24) + (pix.g << 16) + (pix.b << 8) + pix.a;
                    display->set(SDL_row, SDL_col, RawPixel(hex));
                }
                // Outside viewport
                else if(world_row < viewport_y_min || world_row > (viewport_y_max + viewport_thickness) || world_col < viewport_x_min || world_col > (viewport_x_max + viewport_thickness))
                {
                    display->set(SDL_row, SDL_col, RawPixel(0x0));
                }
                else // Viewport border
                {
                    hex = (viewport->border_color << 8) + viewport->border_alpha;
                    display->set(SDL_row, SDL_col, RawPixel(hex));
                }
            }
            else
            {
                pix = buffer.get(world_row, world_col);

                if(pix == background) display->set(SDL_row, SDL_col, RawPixel(0x0));
                else
                {
                    hex = (pix.r << 24) + (pix.g << 16) + (pix.b << 8) + pix.a;
                    display->set(SDL_row, SDL_col, RawPixel(hex));
                }
            }
        }
    }
}

// Reset World's buffer
void World::reset()
{
    for(size_t row = 0; row < height; row++)
    {
        for(size_t col = 0; col < width; col++)
        {
            buffer.set(row, col, Pixel(0, 0, -100));
        }
    }
}

/* Public access */

// Constructors
World::World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col) : buffer(_width, _height)
{
    width = _width;
    height = _height;
    SDL_origin_row = _SDL_origin_row;
    SDL_origin_col = _SDL_origin_col;

    num_polygon = 0;
    fps_count = 0;
}

World::World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col, unsigned int _viewport_row, unsigned int _viewport_col) : buffer(_width, _height)
{
    width = _width;
    height = _height;
    SDL_origin_row = _SDL_origin_row;
    SDL_origin_col = _SDL_origin_col;
    viewport_row = _viewport_row;
    viewport_col = _viewport_col;

    num_polygon = 0;
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

// Add a polygon to World
void World::addPolygon(Polygon* _polygon, vector<ITransform*>* _transform)
{
    polygons.push_back(make_pair(_polygon, _transform));
    num_polygon++;
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