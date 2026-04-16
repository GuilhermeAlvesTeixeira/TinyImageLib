#include <iostream>
#include <cstdint>

#include "ImageBuffer.h"
#include "ImageIO.h"
#include "utils.h"
#include "test_utils.h"

#include "types/Rgb.h"
#include "types/YCbCr.h"
#include "types/Hsv.h"

using namespace TinyImage;

int main() {
    ImageBuffer<RGB> buffer;

    try {
      loadPPM(buffer, "input.ppm");

    } catch (const std::exception& e) {
        std::cerr << "Erro no carregamento: " << e.what() << std::endl;
        return 1;
    }

    ImageBuffer<RGB> original = buffer; 
    const int iteracoes = 100; 

    std::cout << "Iniciando processamento de " << iteracoes << " ciclos..." << std::endl;

    for (int i = 0; i < iteracoes; ++i) {
       
        for (auto it = buffer.begin(); it != buffer.end(); ++it) {
            *it = it->toYCbCr().toHSV().toRGB();
        }

        double mse = computeMSE(original, buffer);
        double psnr = computePSNR(mse);

        std::cout << "Ciclo " << i + 1 << " concluído." << " | MSE: " << mse<< " | PSNR: " << psnr << " dB" << std::endl;
    }

    // 3. Salvar o resultado
    try {
        savePPM(buffer, "saida_ciclo.ppm");
        std::cout << "\nSucesso! Imagem salva como: saida_ciclo.ppm" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao salvar: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}