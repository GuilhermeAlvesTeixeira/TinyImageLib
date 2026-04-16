#ifndef HSV_STRUCT_H
#define HSV_STRUCT_H

// H: [0,360];
// S,V: [0,1]

namespace TinyImage {
    struct HSV {
        float h, s, v;
        RGB toRgb() const;
    };
}
#endif