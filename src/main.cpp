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

int main(int argc, char** argv) {

    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "TinyImageLib CLI\n\n";
        std::cout << "Uso:\n";
        std::cout << "  ./app <input.ppm> <output.ppm> <iteracoes> [--quiet]\n\n";

        std::cout << "Argumentos:\n";
        std::cout << "  input.ppm    Caminho da imagem de entrada (PPM P3)\n";
        std::cout << "  output.ppm   Caminho da imagem de saída\n";
        std::cout << "  iteracoes    Número de ciclos de conversão\n\n";

        std::cout << "Opções:\n";
        std::cout << "  --quiet      Executa sem mostrar métricas por ciclo\n";
        std::cout << "  --help       Mostra esta mensagem\n\n";

        std::cout << "Exemplo:\n";
        std::cout << "  ./app ../assets/input.ppm saida.ppm 100\n";

        return 0;
    }   

    if (argc < 4) {
        std::cout << "Argumentos insuficientes.\n";
        std::cout << "Use --help para ver como utilizar o programa.\n";
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    int iteracoes = std::stoi(argv[3]);

    bool quiet = false;
    if (argc > 4 && std::string(argv[4]) == "--quiet"){
        quiet = true;
    }

    ImageBuffer<RGB> buffer;

    try {
      loadPPM(buffer, inputFile);

    } catch (const std::exception& e) {
        std::cerr << "Erro no carregamento: " << e.what() << std::endl;
        return 1;
    }

    ImageBuffer<RGB> original = buffer; 
   
   // const int iteracoes = 100; 

   //std::cout << "Iniciando processamento de " << iteracoes << " ciclos..." << std::endl;
   
    if (!quiet) {
        std::cout << "Imagem carregada: "
                  << buffer.getWidth() << "x" << buffer.getHeight() << "\n";
        std::cout << "Iteracoes: " << iteracoes << "\n\n";
    }

    for (int i = 0; i < iteracoes; ++i) {
       
        for (auto it = buffer.begin(); it != buffer.end(); ++it) {
            *it = it->toYCbCr().toHSV().toRGB();
        }

        double mse = computeMSE(original, buffer);
        double psnr = computePSNR(mse);

        if(!quiet){
            std::cout << "Ciclo " << i + 1 << " concluído." << " | MSE: " << mse<< " | PSNR: " << psnr << " dB" << std::endl;
        }
    }

    try {
        savePPM(buffer, outputFile);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao salvar: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nImagem salva em: " << outputFile << std::endl;

    return 0;
}