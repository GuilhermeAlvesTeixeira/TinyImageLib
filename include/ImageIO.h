#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <fstream>
#include <string>
#include <exception>

#include "ImageBuffer.h"


template <typename T>
void savePPM(const ImageBuffer<T>& img, const std::string& filename) {
    std::ofstream file(filename);

    if(!file) {
        throw std::runtime_error("Erro ao abrir o arquivo");
    }

    //Importante para .ppm
    file << "P3\n";
    file << img.getWidth() << " " << img.getHeight() << "\n";
    file << "255\n";

    //Pixels
    for(size_t row = 0; row < img.getHeight(); row++) {
        for( size_t col = 0; col < img.getWidth(); col++) {
            const auto& pixel = img.getPixel(row,col);

            file << (int) pixel.r << " "
                 << (int) pixel.g << " "
                 << (int) pixel.b << " ";
        }
        file << "\n";
    } 
}

#endif