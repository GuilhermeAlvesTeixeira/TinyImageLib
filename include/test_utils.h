#include <cmath>
#include "ImageBuffer.h"

#include "types/Rgb.h"

/*
*   Não entendi direito, mas ao que parece o MSE é ruim de interpretar e, 
*   portanto, entra o PSNR (Peak Signal-to-Noise Ratio ou Relação Sinal-Ruído de Pico) 
*   para medir quanto o sinal (imagem original) é mais forte que o ruído (erro).
*
*
*   Interpretação (PSNR)
*      ∞        - identico
*   > 40 db     - excelente
*   30 - 40 db  - ok
*   < 30 db     - degradação visível
*
*/

double computeMSE(const ImageBuffer<TinyImage::RGB>& a, const ImageBuffer<TinyImage::RGB>& b) {
    if(a.getWidth() != b.getWidth() || a.getHeight() != b.getHeight()) {
        throw std::runtime_error("Imagens com tamanho diferentes!");
    }

    double mse = 0.0;
    size_t totalPixels = a.getWidth() * a.getHeight();

    for(size_t row = 0; row < a.getHeight(); row++){
        for(size_t col = 0; col < a.getWidth(); col++) {
            const auto& p1 = a.getPixel(row, col);
            const auto& p2 = b.getPixel(row,col);
            
            //MSE = (1/n) * sum(I - Iprocessado)²
            double dr = p1.r - p2.r;
            double dg = p1.g - p2.g;
            double db = p1.b - p2.b;

            mse += dr * dr + dg * dg + db * db;
        }
    }
    return mse / (totalPixels * 3.0);
}

double computePSNR(double mse) {
    if(mse == 0.0) return INFINITY;
    return 10.0 * log10((255.0 * 255.0)/mse);
}