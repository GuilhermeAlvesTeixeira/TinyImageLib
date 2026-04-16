#include <iostream>
#include <cstdint>

#include "Image2D.h"
#include "ImageBuffer.h"
#include "utils.h"
#include "ImageIO.h"

#include "types/Rgb.h"
#include "types/YCbCr.h"
#include "types/Hsv.h"


int main(int argc, char** argv) {

    // Usando ImageBuffer.h

    ImageBuffer<TinyImage::RGB> img (8,8);
    img.clear(TinyImage::RGB(255,0,0));
    fillRandomRGB(img);

    /*
    for (size_t i = 0; i < img.getHeight(); i++) {
        for (size_t j = 0; j < img.getWidth(); j++) {
            printPixel(img.getPixel(i,j));
        }
        std::cout << '\n';
    }*/

    for(const auto& pixel : img) {
         printPixel(pixel);
         std::cout << " " << '\n';
    }

    savePPM(img, "output.ppm");

    return 0;

    /* 
    
    // ANTIGO: USANDO Image2D

    Image2D<size_t> img(4,3);

    img.clear(0);

    img.setPixel(1,1,255);
    img.setPixel(2,0,128);

    for(size_t row = 0; row < img.getHeight(); row++) {
        for( size_t col = 0; col < img.getWidth(); col++) {
            std::cout << img.getPixel(row,col) << " ";
        }
        std::cout << '\n';
    }
    return 0;
    */

}