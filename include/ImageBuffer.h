#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>

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

    size_t index(size_t rows, size_t columns) const {
        return rows * width + columns;
    }

public:
    ImageBuffer() = default;
    ImageBuffer(size_t w, size_t h) : width(w), height(h), data(w * h) {}

    //Operator
    T& operator() (size_t row, size_t col) { return data[index(row, col)];}
    const T& operator() (size_t row, size_t col) const { return data[index(row, col)];}

    // Métodos acessores (GETTERS)
    auto getWidth() const   { return width; }
    auto getHeight() const { return height; }

    // Métodos acessores pixel (GET e SET)
    T& getPixel(size_t row, size_t col){
        if(col >= width || row >= height) {
            throw std::out_of_range("Índice fora dos limites da Imagem!");
        }
        return data[index(row, col)];
    }

    const T& getPixel(size_t row, size_t col) const {
        if (col >= width || row >= height) {
            throw std::out_of_range("Índice fora dos limites da Imagem!");
        }
        return data[index(row, col)];
    }



    void setPixel(size_t row, size_t col, const T& value ) {
        if(col >= width || row >= height) {
            throw std::out_of_range("Índice fora dos limites Imagem!");
        }   
        data[index(row, col)] = value;
    }

    void clear(const T& value) {
        std::fill(data.begin(), data.end(), value);
    }

    //Acesso Direto
    T* rawData() {
        return data.data();
    }

    const T* rawData() const {
        return data.data();
    }

    // Iteradores
    auto begin() {return data.begin();}
    auto end() {return data.end();}

    auto begin() const {return data.begin();}
    auto end() const {return data.end(); }

};

#endif