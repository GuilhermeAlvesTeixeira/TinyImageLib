# TinyImageLib

TinyImageLib é uma biblioteca simples em C++ para manipulação de imagens 2D baseada em templates.
O objetivo do projeto é servir como um ambiente didático e experimental para entender conceitos fundamentais aprendidos na disciplina de Computação Gráfica, como:

* Estruturas de dados lineares aplicadas a imagens
* Templates em C++
* Iteradores
* Escrita de formatos de imagem sem bibliotecas externas

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
* Acesso direto ao buffer com `rawData()` (futura integração com bibliotecas gráficas externas)

---

### Exportação de imagem (PPM - P3)

* Escrita de imagens no formato `.ppm` (modo texto)
* Não utiliza bibliotecas externas
* Compatível com visualizadores como GIMP, ImageMagick, etc.

---

## Como clonar, compilar e executar

```bash
git clone https://github.com/GuilhermeAlvesTeixeira/TinyImageLib
mkdir build
cd build
cmake ..
make
make run
```

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

### Resultado

O arquivo gerado (`polar_gradient.ppm`) pode ser aberto com:

```bash
xdg-open polar_gradient.ppm
```

ou em softwares de imagem como:

* GIMP
* Krita
* ImageMagick

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

## Próximos passos (roadmap)

* [ ] Exportação binária (PPM P6)
* [ ] Suporte a grayscale (PGM)
* [ ] Leitura de arquivos `.ppm`
* [ ] Sistema de traits para pixels genéricos
* [ ] Filtros de imagem (invert, blur, edge detection)
* [ ] Operações funcionais (map, transform)
* [ ] Paralelismo e otimização

---

## Objetivo do projeto

Este projeto não busca substituir bibliotecas como OpenCV, mas sim:

* Ensinar como imagens funcionam internamente
* Explorar design moderno em C++
* Servir como base para projetos maiores (renderização, engines, etc.)

---

## Autor

Guilherme Alves Teixeira

---

## Licença

Este projeto está licenciado sob a licença MIT.
