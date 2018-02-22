#include "SDLDisplay.h"

#include <signal.h>

using namespace std;

// Constructor
SDLDisplay::SDLDisplay(size_t _width, size_t _height) : buffer(_width, _height)
{
    width = _width;
    height = _height;

    struct sigaction action;

    sigaction(SIGINT, NULL, &action);
    SDL_Init(SDL_INIT_VIDEO);
    sigaction(SIGINT, &action, NULL);

    window = SDL_CreateWindow("IF3260", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0);
    //SDL_SetWindowResizable(window, SDL_FALSE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC, _width, _height);
}

// Destructor
SDLDisplay::~SDLDisplay()
{
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

// Getter
RawPixel SDLDisplay::get(size_t _row, size_t _col) { return buffer.get(_row, _col); }

// Setter
void SDLDisplay::set(size_t _row, size_t _col, RawPixel _rawPixel) { buffer.set(_row, _col, _rawPixel); }

// Render
void SDLDisplay::render()
{
    SDL_UpdateTexture(texture, NULL, buffer.data, width * sizeof(RawPixel));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}