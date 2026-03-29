#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>
#include <iostream>

/*
    Nova ideia: Todos os pixels estão em uma fila única e contínua (vector<T>)
    data[rows][col]  →  data[rows * width + col]
    */

template<typename T>

class ImageBuffer {

private:
    std::vector<T> data;
    size_t width;
    size_t height;


public:

};

#endif