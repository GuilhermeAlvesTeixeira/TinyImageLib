#ifndef YCBCR_STRUCT_H
#define YCBCR_STRUCT_H

#include <iostream>
#include <cstdint>

/* Nota (pq eu não lembrava): YCbCr tenta separar luminãncia (brilho) de crominânica (cor).
   Y -> brilho (luminância)
   Cb -> componente azul (quanto a cor se afasta para o azul)
   Cr -> componente vermelho (quanto a cor se afasta para o vermelho)

   O olho humano é muito mais sensível ao brilho do que à cor.
*/

//Y: [0,255]
//CbCr: [-128, 127]

namespace TinyImage {
    struct RGB;
    struct HSV;

    struct YCbCr {
        float y, cb, cr;
        RGB toRGB() const;
        HSV toHSV() const;
    };
}


#endif