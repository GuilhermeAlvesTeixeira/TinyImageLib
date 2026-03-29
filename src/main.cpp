#include <iostream>

#include "Image2D.h"
#include "ImageBuffer.h"

int main(int argc, char** argv) {

    //NOVO: Usando ImageBuffer.h

    ImageBuffer<int> img (4,4);
    img.clear(0);
    img.setPixel(2,2,1.0f);

    std::cout << img.getPixel(2,2) << '\n';

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