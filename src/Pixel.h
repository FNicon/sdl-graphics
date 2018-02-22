#pragma once

class Pixel
{
    public:
        // Colors
        unsigned int r;
        unsigned int g;
        unsigned int b;

        // Transparency
        unsigned int a;

        // Layer (z-index)
        int layer;

        // Constructors
        Pixel() = default;

        Pixel(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a, int _layer = 0)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
            layer = _layer;
        }

        Pixel(unsigned int _color, unsigned int _alpha, int _layer = 0)
        {
            r = _color >> 16;
            g = (_color >> 8) & 0xFF;
            b = _color & 0xFF;
            a = _alpha;
            layer = _layer;
        }

        // Comparator
        friend bool operator== (const Pixel& _lhs, const Pixel& _rhs)
        {
            return (_lhs.r == _rhs.r) && (_lhs.g == _rhs.g) && (_lhs.b == _rhs.b) && (_lhs.a == _rhs.a);
        }
};