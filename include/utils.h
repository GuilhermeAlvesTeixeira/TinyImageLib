#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdint>
#include <random>
#include <chrono>

#include "types/Rgb.h"
#include "ImageBuffer.h"

template<typename T>
void printPixel(const T& value) {
    std::cout << value;
}


//Especialização do RGB
template <>
void printPixel<RGB>(const RGB& value) {
    std::cout << "("
              << static_cast<int>(value.r) << ", " 
              << static_cast<int>(value.g) << ", "  
              << static_cast<int>(value.b) << ")"; 
}

void fillRandomRGB(ImageBuffer<RGB>& img) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0,255);

    for (auto& pixel : img) {
        pixel = RGB(dist(gen), dist(gen), dist(gen));
    }

    /*
    for(size_t row = 0; row < img.getHeight(); row++) {
        for(size_t col = 0; col < img.getWidth(); col++) {
            uint8_t r = static_cast<uint8_t>(dist(gen));
            uint8_t g = static_cast<uint8_t>(dist(gen));
            uint8_t b = static_cast<uint8_t>(dist(gen));

            img.setPixel(row,col,RGB(r,g,b));
        }
    }*/

   /*
   size_t totalPixels = img.getWidth() * img.getHeight();
   RGB* ptr = img.rawData();

   for(size_t i = 0; i < totalPixels; i++) {
    ptr[i] = RGB(dist(gen), dist(gen), dist(gen));
   }*/
}

#endif