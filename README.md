# TinyImageLib

TinyImageLib é uma biblioteca simples em C++ para manipulação de imagens 2D baseada em templates.
O objetivo do projeto é servir como um ambiente didático e experimental para entender conceitos fundamentais aprendidos na disciplina de Computação Gráfica, como:

* Estruturas de dados lineares aplicadas a imagens
* Templates em C++
* Iteradores
* Escrita e leitura de formatos de imagem sem bibliotecas externas
* Conversões entre espaços de cor e seus impactos

---

## Funcionalidades

### Estrutura de imagem

* Classe genérica `ImageBuffer<T>`
* Armazenamento contínuo em memória (`std::vector<T>`)
* Acesso por:

  * Coordenadas `(row, col)`
  * Iteração linear (`range-based for`)

---

### Manipulação de pixels

* `setPixel(row, col, value)`
* `getPixel(row, col)`
* `clear(value)` — preenche toda a imagem
* Acesso direto ao buffer com `rawData()` (integração futura com APIs gráficas)

---

## Espaços de cor suportados

A biblioteca agora suporta múltiplas representações de cor:

* **RGB**
* **YCbCr** (baseado na ITU-R BT.601 — full range)
* **HSV**

---

## Conversões implementadas

* RGB → YCbCr
* YCbCr → RGB
* YCbCr → HSV (via RGB)
* HSV → RGB

As conversões seguem modelos clássicos utilizados em:

* Compressão de imagem (JPEG)
* Processamento de vídeo
* Ferramentas gráficas

---

## Entrada e saída de imagem

### Escrita (PPM - P3)

* Exportação de imagens no formato `.ppm` (modo texto)
* Não utiliza bibliotecas externas
* Compatível com:

  * GIMP
  * Krita
  * ImageMagick

---

### Leitura (PPM - P3)

* Suporte a carregamento de imagens `.ppm`
* Leitura do header (`P3`, dimensões, max value)
* Suporte a comentários (`#`)
* Alocação automática do `ImageBuffer`

---

## Estrutura do Projeto

* `ImageBuffer<T>` → buffer genérico de pixels
* `types/` → implementações de `RGB`, `YCbCr`, `HSV`
* `ImageIO.h` → leitura e escrita de imagens
* `test_utils.h` → métricas de erro (MSE / PSNR)

---

## Métricas de Qualidade

### MSE (Mean Squared Error)

Mede o erro médio ao quadrado entre duas imagens:

```
MSE = (1/N) * Σ (I_original - I_processado)²
```

* Penaliza diferenças maiores de forma mais intensa
* Útil para cálculo, mas difícil de interpretar diretamente

---

### PSNR (Peak Signal-to-Noise Ratio)

Derivado do MSE:

```
PSNR = 10 * log10(255² / MSE)
```

Interpretação:

```
∞        → imagens idênticas
> 40 dB  → excelente
30–40 dB → aceitável
< 30 dB  → degradação visível
```

O PSNR é medido em **decibéis (dB)**, uma escala logarítmica que representa a relação entre:

* **Sinal** → imagem original
* **Ruído** → erro introduzido

---

# OBS: PARA PROFESSOR GILVAN

## ▶️ Como compilar e executar (CLI)

### 1. Compilação

Na raiz do projeto:

```bash
mkdir build
cd build
cmake ..
make
```

### 2. Execução

O programa utiliza uma interface de linha de comando (CLI):

```bash
./app <input.ppm> <output.ppm> <iteracoes> [--quiet]
```
Parâmetros:
```input.ppm``` → imagem de entrada (PPM P3)
```output.ppm``` → imagem de saída
```iteracoes``` → número de ciclos de conversão
```--quiet``` → (opcional) desativa logs no terminal

### 3. Exemplos de uso
A partir da raiz do projeto:
```bash
./build/app assets/input.ppm saida.ppm 100
```

Ou dentro da pasta ```build```
```bash
./app ../assets/input.ppm saida.ppm 100
```

### 4. Ajuda
```bash
./app --help
```

---

## Experimento: Estresse de Conversões

O `main.cpp` implementa um experimento para analisar degradação de imagem.

### Pipeline aplicado

```
RGB → YCbCr → HSV → RGB
```

Esse processo é executado repetidamente (ex: 100 ciclos).

---

### Objetivo

Avaliar:

* Acúmulo de erro
* Perda de informação
* Impacto de múltiplas conversões

---

### Comportamento observado

A cada ciclo:

* Conversões introduzem pequenas imprecisões
* Ocorre quantização (float → uint8)
* Transformações não-lineares (HSV) amplificam o erro

Resultado:

* MSE aumenta
* PSNR diminui
* A imagem perde qualidade progressivamente

---

### Exemplo de saída

<img width="652" height="247" alt="image" src="https://github.com/user-attachments/assets/7e57ff15-d44e-4a1f-9c91-3c51cc208f94" />

---

### Comparação visual

Recomenda-se comparar:

* Imagem original
* Imagem após 100 ciclos

Resultados:
* Utilizando um visualizador de 'ppm' online:
https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html

| Imagem Original | Após 100 ciclos |
|----------------|-----------------|
| <img src="https://github.com/user-attachments/assets/1fa4df57-a2ec-4fa8-99df-a18029e3b798" width="300"/> | <img src="https://github.com/user-attachments/assets/e76f1120-fa0c-4b03-a231-893ca5c2c854" width="300"/> |

---

### Diferenças observadas

| Aspecto           | Observação                                      |
|------------------|-------------------------------------------------|
| Saturação        | Redução perceptível (cores mais “lavadas”)      |
| Fidelidade de cor| Pequenas alterações acumuladas                  |
| Contraste        | Leve perda em regiões específicas               |
| Erro acumulado   | Múltiplas conversões + quantização              |
| PSNR             | Diminui ao longo dos ciclos                     |

---

## Exemplo de uso

### 1. Definir um pixel RGB

```cpp
struct RGB {
    uint8_t r, g, b;

    RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        : r(r), g(g), b(b) {}
};
```

---

### 2. Gerar uma imagem procedural (gradiente polar)

```cpp
const int size = 500;
ImageBuffer<RGB> img(size, size);

float centerX = size / 2.0f;
float centerY = size / 2.0f;

for (size_t row = 0; row < img.getHeight(); row++) {
    for (size_t col = 0; col < img.getWidth(); col++) {
        float dx = col - centerX;
        float dy = row - centerY;

        float angle = std::atan2(dy, dx);
        float normAngle = (angle + M_PI) / (2.0f * M_PI);

        float radius = std::sqrt(dx * dx + dy * dy) / centerX;

        if (radius > 1.0f) radius = 1.0f;

        uint8_t r = static_cast<uint8_t>(normAngle * 255);
        uint8_t g = static_cast<uint8_t>((1.0f - normAngle) * 255);
        uint8_t b = static_cast<uint8_t>(radius * 255);

        img.setPixel(row, col, RGB(r, g, b));
    }
}
```

---

### 3. Exportar como `.ppm`

```cpp
savePPM(img, "polar_gradient.ppm");
```

---

## Saída (Exemplo)

<img width="765" height="596" alt="image" src="https://github.com/user-attachments/assets/7b35e1b0-3673-4ee2-8a7e-00fb878501a5" />

---

## Como funciona o formato PPM (P3)

O formato PPM em modo texto é extremamente simples:

```
P3
<width> <height>
255
R G B R G B ...
```

Cada pixel é representado por três valores (RGB) no intervalo `[0, 255]`.

---

## Objetivo do projeto

Este projeto não busca substituir bibliotecas como OpenCV, mas sim:

* Ensinar como imagens funcionam internamente
* Explorar design moderno em C++
* Investigar transformações de cor e erro numérico
* Servir como base para projetos maiores (renderização, engines, etc.)

---

## Autor

Guilherme Alves Teixeira

---

## Licença

Este projeto está licenciado sob a licença MIT.
