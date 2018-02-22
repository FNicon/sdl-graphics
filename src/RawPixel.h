#pragma once

struct RawPixel
{
    // Colors
    unsigned char b;
    unsigned char g;
    unsigned char r;

    // Transparency
    unsigned char a;

    // Constructors
    RawPixel() = default;
    RawPixel(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : b(_b), g(_g), r(_r), a(_a) {}
    RawPixel(unsigned int _hex) : b(_hex >> 8 & 0xff), g(_hex >> 16 & 0xff), r(_hex >> 24 & 0xff), a(_hex & 0xff) {}

    // Comparator
    friend bool operator== (const RawPixel& _lhs, const RawPixel& _rhs)
    {
        return (_lhs.b == _rhs.b) && (_lhs.g == _rhs.g) && (_lhs.r == _rhs.r) && (_lhs.a == _rhs.a);
    }
};