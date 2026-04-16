#include "types/Rgb.h"
#include "types/YCbCr.h"
#include "types/Hsv.h"
#include <cmath>
#include <algorithm>

/*
*    Referências:
*
*    - ITU-R BT.601 (SDTV): base dessas constantes
*    https://www.itu.int/rec/R-REC-BT.601
*
*    - ITU-R BT.709 (HDTV): variação moderna
*    https://www.itu.int/rec/R-REC-BT.709
*
*    ICC (International Color Consortium):
*    https://www.color.org
*
*    Obs: O código em questão segue o modelo clássico YCbCr (BT.601 full range)
*
*/

// OBS: IMPORTANTE!!!

/*
    Por padrão, Cb e Cr são armazenados no intervalo [0, 255], contudo, conceitualmente
    representam valores centrados em 0:

    Cb, Cr ∈ [-128, +127]

    O offset de +128 é aplicado para evitar valores negativos em representações de 8 bits (uint_8).
    
    Portanto, para recuperar o valor real:

    valor_real = valor_armazenado - offset
*/
static constexpr float offset = 128.0f;

namespace TinyImage {
    // RGB -> YCbCr
    YCbCr RGB::toYCbCr() const {
        return {
            //Luminância: ITU-R BT.601-7 (p.4)
            0.299f * r + 0.587f * g + 0.114f * b,
            //Cb: Normalização do Cb
            -0.168736f * r - 0.331264f * g + 0.500f * b + offset,
            //Cr: Normalização do Cr
            0.500f * r - 0.418688f * g - 0.081312f * b + offset
        };
    }

    RGB YCbCr::toRGB() const {
        //Removendo offset - consultar comentário no início do código.
        float cb_s = cb - offset;
        float cr_s = cr - offset;

        //R = Y + contribuição do vermelho (CR)
        float fr = y + 1.402f * cr_s;

        //G = Y - contribuição do azul (Cb) e vermelho (Cr)
        float fg = y - 0.344136f * cb_s - 0.714136f * cr_s;

        //B = Y + contribuição do azul (Cb)
        float fb = y + 1.772f * cb_s;

        return RGB(
            static_cast<uint8_t>(std::clamp(fr, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(fg, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(fb, 0.0f, 255.0f))
        );
    }

    HSV YCbCr::toHSV() const {
            RGB rgb = this->toRGB();

            //Normalizando para intervalo [0,1]
            // Assumindo YCbCr full range (0–255).
            float fr = rgb.r / 255.0f;
            float fg = rgb.g / 255.0f;
            float fb = rgb.b / 255.0f;

            float max = std::max({fr, fg, fb});
            float min = std::min({fr, fg, fb});
            float delta = max - min;

            HSV hsv;
            hsv.v = max; // brilho
            hsv.s = (max > 0.0f) ? (delta / max) : 0.0f;

            if (delta > 0.0f) {
                if (max == fr)
                    hsv.h = 60.0f * fmod(((fg - fb) / delta), 6.0f);
                else if (max == fg)
                    hsv.h = 60.0f * (((fb - fr) / delta) + 2.0f);
                else
                    hsv.h = 60.0f * (((fr - fg) / delta) + 4.0f);

                if (hsv.h < 0) hsv.h += 360.0f;
            } else {
                hsv.h = 0.0f;
            }

            return hsv;
        }

    // HSV -> RGB
    RGB HSV::toRGB() const {
        float r_f = 0, g_f = 0, b_f = 0;

        if (s == 0.0f) {
            // Caso acromático (cinza)
            r_f = g_f = b_f = v;
        } else {
            float sector = h / 60.0f;      // setor 0 a 5
            int i = static_cast<int>(floor(sector));
            float f = sector - i;          // parte fatorial do setor
            
            float p = v * (1.0f - s);
            float q = v * (1.0f - s * f);
            float t = v * (1.0f - s * (1.0f - f));

            switch (i % 6) {
                case 0: r_f = v; g_f = t; b_f = p; break;
                case 1: r_f = q; g_f = v; b_f = p; break;
                case 2: r_f = p; g_f = v; b_f = t; break;
                case 3: r_f = p; g_f = q; b_f = v; break;
                case 4: r_f = t; g_f = p; b_f = v; break;
                case 5: r_f = v; g_f = p; b_f = q; break;
            }
        }

        return RGB(
            static_cast<uint8_t>(std::clamp(r_f * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(g_f * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(b_f * 255.0f, 0.0f, 255.0f))
        );
    }
}
