#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>
#include <iostream>
#include <exception>

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

    size_t index(size_t rows, size_t columns) {
        return rows * width + columns;
    }

public:
    ImageBuffer() = default;
    ImageBuffer(size_t w, size_t h) : width(w), height(h), data(w * h) {}

    // Métodos acessores (GETTERS)
    auto getWidth() const   { return width; }
    auto getHeight() const { return height; }

    // Métodos acessores pixel (GET e SET)
    auto getPixel(size_t row, size_t col){
        if(col < 0 || col >= width || row < 0 || row >= height) {
            throw std::out_of_range("Índice fora dos limites Imagem!");
        }
        return data[index(row, col)];
    }

    void setPixel(size_t row, size_t col, const T& value ) {
        if(col < 0 || col >= width || row < 0 || row >= height) {
            throw std::out_of_range("Índice fora dos limites Imagem!");
        }   
        data[index(row, col)] = value;
    }

};

#endif