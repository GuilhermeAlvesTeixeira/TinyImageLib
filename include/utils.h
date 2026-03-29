#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdint>

#include "types/Rgb.h"

template<typename T>
void printPixel(const T& value) {
    std::cout << value;
}

//Especialização do RGB
template <>
void printPixel<RGB>(const RGB& value) {
    std::cout << "("
              << (uint8_t) value.r << ", "
              << (uint8_t) value.g << ", "
              << (uint8_t) value.b << ")";
}

void randomRGBImg() {

}

#endif