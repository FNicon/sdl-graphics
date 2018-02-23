#pragma once

#include "Buffer.h"
#include "Pixel.h"
#include "SDLDisplay.h"
#include "Polygon.h"
#include "ITransform.h"

class World
{
    private:
        void draw(); // Draw polygon to buffer
        void transform(); // Transform all Polygons in World
        void flush(); // Flush World's buffer to SDL's buffer
        void reset(); // Reset World's buffer

    public:
        // Size
        size_t width;
        size_t height;

        // Buffer
        Buffer<Pixel> buffer;

        // Pointer to SDL Display
        SDLDisplay* display = nullptr;

        // SDL Display's origin point relative to World
        unsigned int SDL_origin_row;
        unsigned int SDL_origin_col;

        // Use viewport?
        bool viewport = false;

        // Viewport's origin point relative to SDL display
        unsigned int viewport_row;
        unsigned int viewport_col;

        // Counters
        size_t num_polygon; // Number of polygons
        size_t num_transform; // Number of transformations

        unsigned int fps_count;

        // List of pointer to Polygon
        vector<Polygon*> polygons;

        // List of transformations
        vector<ITransform*> transformation;

        // Support Group and multiple transformations

        // Constructors
        World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col);
        World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col, unsigned int _viewport_row, unsigned int _viewport_col);
        
        // Getter, coordinate relative to SDL display origin point
        Pixel get(size_t _row, size_t _col);

        // Setter, coordinate relative to SDL display origin point
        void set(size_t _row, size_t _col, Pixel _pixel);

        // Add a polygon to World
        void addPolygon(Polygon* _polygon);

        // Add polygon transformation
        void addTransformation(ITransform* _transform);

        // Render (sort by layer, transform, clipping, floodfill, write to buffer, copy to SDL's buffer, invoke SDL's render)
        void render(unsigned int fps = 0);
};