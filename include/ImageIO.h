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

template <typename T>
void loadPPM(ImageBuffer<T>& img, const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Erro ao abrir o arquivo");
    }

    std::string magic;
    file >> magic;

    if (magic != "P3") {
        throw std::runtime_error("Formato não suportado (esperado P3)");
    }

    // Função auxiliar pra pular comentários
    auto skipComments = [&file]() {
        while (file >> std::ws && file.peek() == '#') {
            std::string line;
            std::getline(file, line);
        }
    };

    skipComments();

    size_t width, height;
    file >> width >> height;

    skipComments();

    int maxVal;
    file >> maxVal;

    if (maxVal != 255) {
        throw std::runtime_error("Somente maxVal = 255 suportado");
    }

    img = ImageBuffer<T>(width, height);

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            int r, g, b;
            file >> r >> g >> b;

            img.getPixel(row, col) = T(
                static_cast<uint8_t>(r),
                static_cast<uint8_t>(g),
                static_cast<uint8_t>(b)
            );
        }
    }
}

#endif