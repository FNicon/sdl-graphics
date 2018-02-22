#pragma once

#include <SDL.h>
#include <stdexcept>

#include "Buffer.h"
#include "RawPixel.h"

class SDLDisplay
{
    private:
        // SDL Window
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

    public:
        // Size
        size_t width;
        size_t height;

        // Buffer
        Buffer<RawPixel> buffer;

        // Constructor
        SDLDisplay(size_t _width, size_t _height);

        // Destructor
        ~SDLDisplay();

        // Getter
        RawPixel get(size_t _row, size_t _col);

        // Setter
        void set(size_t _row, size_t _col, RawPixel _rawPixel);

        // Render
        void render();
};