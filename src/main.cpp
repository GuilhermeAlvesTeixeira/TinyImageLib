#include <iostream>
#include <cstdint>


#include "Image2D.h"
#include "ImageBuffer.h"
#include "utils.h"

int main(int argc, char** argv) {

    // Usando ImageBuffer.h

    ImageBuffer<RGB> img (8,8);
    img.clear(RGB(255,0,0));
    img.setPixel(2,2,RGB(128,0,0));

    for (size_t i = 0; i < img.getHeight(); i++) {
        for (size_t j = 0; j < img.getWidth(); j++) {
            printPixel(img.getPixel(i,j));
        }
        std::cout << '\n';
    }

    //std::cout << img.getPixel(2,2) << '\n';
    

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