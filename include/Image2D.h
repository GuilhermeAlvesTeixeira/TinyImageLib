#ifndef IMAGE2D_H
#define IMAGE2D_H

#include <iostream>
#include <exception>

template<typename T>

class Image2D {
private:
    T** data;
    size_t width;
    size_t height;

public:
    //Construtores
    Image2D();
    Image2D(size_t w, size_t h) : width(w), height(h) {
        data = new T*[height]; //Aloca array de ponteiros (linhas)

        for(size_t i=0; i < height; i++) {
            data[i] = new T[width]; // p/cada linha, aloca um array de T colunas.
        }
    };

    //Destrutor
    ~Image2D() {
        for(size_t i = 0; i < height; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }

    //Métodos acessores (GET)
    
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    //Métodos acessores PIXEL (SET e GET)
    //Lembrete: col -> largura | row -> altura

    void setPixel(int row, int col , const T& value) {
        if(col < 0 || col >= width || row < 0 || row >= height) {
            throw std::out_of_range("Índice fora dos limites Imagem!");
        }
        data[row][col] = value;
    }

    T getPixel(int row, int col) {
        if(col < 0 || col >= width || row < 0 || row >= height) {
            throw std::out_of_range("Índice fora dos limites Imagem!");
        }
        return data[row][col];
    }

    //Clear: Preenchimento
    void clear(const T& value) {
        for(size_t row = 0; row < height; row++) {
            for(size_t col = 0; col < width; col++) {
                data[row][col] = value;
            }
        }
    }

    //Bloqueio de Cópia (Regra dos três: Sugerido pelo prof Gilvan)
    Image2D(const Image2D& other) = delete;
    Image2D& operator = (const Image2D& other) = delete;

};

#endif