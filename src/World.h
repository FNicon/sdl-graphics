#pragma once

#include "Buffer.h"
#include "Pixel.h"
//#include "SDLDisplay.h"
#include "Framebuffer.h"
#include "IShape.h"
#include "ITransform.h"
#include "Viewport.h"

#include <utility>

using namespace std;

class World
{
    private:
        // Comparison function for sorting
        static bool compare(const pair< IShape*, vector<ITransform*>* >& p1, const pair< IShape*, vector<ITransform*>* >& p2);

        void draw(); // Clip, draw and fill shapes to buffer, draw viewport
        void transform(); // Transform all shapes in World
        void flush(); // Flush World's buffer to SDL's buffer
        void reset(); // Reset World's buffer

        unsigned int fps_count; // fps counter
        int fps_reset; // how many times to reset fps
        unsigned int elapsed_frames; // how many elapsed frames before reset

    public:
        // Size
        size_t width;
        size_t height;

        // Buffer for Pixels
        Buffer<Pixel> buffer;

        // Background color
        unsigned int background_color;

        // Pointer to Framebuffer
        Framebuffer* display = nullptr;

        // SDL Display's origin point relative to World
        unsigned int SDL_origin_row;
        unsigned int SDL_origin_col;

        // Pointer to Viewport
        Viewport* viewport = nullptr;

        // List of viewport's tranformations
        vector<ITransform*>* viewport_trans;

        // Counters
        size_t num_shapes; // Number of shapes
        size_t num_viewport_trans; // Number of viewport transformations

        // List of pair (pointer to Shapes, pointer to its transformations)
        vector< pair< IShape*, vector<ITransform*>* > > shapes;

        // Constructors
        World(size_t _width, size_t _height, unsigned int _SDL_origin_row, unsigned int _SDL_origin_col, unsigned int _background_color = 0);
        
        // Getter, coordinate relative to SDL display origin point
        Pixel get(size_t _row, size_t _col);

        // Setter, coordinate relative to SDL display origin point
        void set(size_t _row, size_t _col, Pixel _pixel);

        // Reset fps_count, animation will start from beginning
        void resetFPSCount(unsigned int _elapsed_frames, int _fps_reset);

        // Add a shape and its transformations to World
        void addShape(IShape* _shape, vector<ITransform*>* _transform = nullptr);

        // Add viewport transformations
        void addViewportTrans(vector<ITransform*>* _transform = nullptr);

        // Render (sort by layer, transform, clipping, floodfill, write to buffer, copy to SDL's buffer, invoke SDL's render)
        void render(unsigned int fps = 0);
};