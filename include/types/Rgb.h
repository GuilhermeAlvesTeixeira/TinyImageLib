#ifndef RGB_STRUCT_H
#define RGB_STRUCT_H

#include <iostream>
#include <cstdint>

namespace TinyImage {

    struct YCbCr;

    struct RGB {
        uint8_t r,g,b;
        RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b){}
        
        YCbCr toYCbCr() const;
    };
}


#endif