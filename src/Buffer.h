#pragma once

#include <iostream>

using namespace std;

template<typename Type>
class Buffer
{
    public:
        // Size
        size_t width = 0;
        size_t height = 0;
        
        // Data
        Type* data = nullptr;

        // Constructor
        Buffer(size_t _width, size_t _height)
        {
            width = _width;
            height = _height;

            data = new Type [_height * _width]();
        }

        // Destructor
        ~Buffer() { delete[] data; }

        // Getter
        Type get(size_t _row, size_t _col) { return data[width * _row + _col]; }

        // Setter
        void set(size_t _row, size_t _col, Type _type) { data[width * _row + _col] = _type; }
};