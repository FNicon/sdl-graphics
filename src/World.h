#pragma once

#include "Buffer.h"
#include "Pixel.h"
#include "SDLDisplay.h"

class World
{
    private:
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

        // List of Polygons

        // Constructors
        World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col);
        World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col, unsigned int _viewport_row, unsigned int _viewport_col);
        
        // Getter, coordinate relative to SDL display origin point
        Pixel get(size_t _row, size_t _col);

        // Setter, coordinate relative to SDL display origin point
        void set(size_t _row, size_t _col, Pixel _pixel);

        // Render (sort by layer, transform, clipping, floodfill, write to buffer, copy to SDL's buffer, invoke SDL's render)
        void render();
};