#pragma once

#include <linux/fb.h>

#include "Buffer.h"
#include "RawPixel.h"

class Framebuffer
{
    private:
        int fd; // file descriptor
        struct fb_var_screeninfo var_info; // screen variable info
        struct fb_fix_screeninfo fix_info; // screen fixed info
        char* fb; // pointer to Framebuffer
        
    public:
        long int size; // size in bytes

        // Size
        size_t width;
        size_t height;

        // Buffer
        Buffer<RawPixel> buffer;

        // Constructor
        Framebuffer();

        // Destructor
        ~Framebuffer();

        // Getter
        RawPixel get(size_t _row, size_t _col);

        // Setter
        void set(size_t _row, size_t _col, RawPixel _rawPixel);

        // Render
        void render();
};