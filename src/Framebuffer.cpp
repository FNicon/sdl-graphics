#include "Framebuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

// Constructor
Framebuffer::Framebuffer() : buffer()
{
    fd = open("/dev/fb0", O_RDWR);

    if(fd == -1) exit(1);
    if(ioctl(fd, FBIOGET_FSCREENINFO, &fix_info) == -1) exit(2);
    if(ioctl(fd, FBIOGET_VSCREENINFO, &var_info) == -1) exit(3);

    size = var_info.xres * var_info.yres * var_info.bits_per_pixel / 8;
    width = var_info.xres;
    height = var_info.yres;

    buffer.allocate(width, height);

    fb = (char*) mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(fb == MAP_FAILED) exit(4);
}

// Destructor
Framebuffer::~Framebuffer()
{
    munmap(fb, size);
    close(fd);
}

// Getter
RawPixel Framebuffer::get(size_t _row, size_t _col) { return buffer.get(_row, _col); }

// Setter
void Framebuffer::set(size_t _row, size_t _col, RawPixel _rawPixel) { buffer.set(_row, _col, _rawPixel); }

// Render
void Framebuffer::render()
{
    for(size_t row = 0; row < height; row++)
    {
        for(size_t col = 0; col < width; col++)
        {
            long int offset = (row + var_info.yoffset) * fix_info.line_length + (col + var_info.xoffset) * (var_info.bits_per_pixel / 8);
            RawPixel pix = get(row, col);

            *(fb + offset + 0) = pix.b; // Blue
            *(fb + offset + 1) = pix.g; // Green
            *(fb + offset + 2) = pix.r; // Red
            *(fb + offset + 3) = pix.a; // Alpha
        }
    }
}