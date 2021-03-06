#ifndef CELOFAN_PICOPNG_H
#define CELOFAN_PICOPNG_H

#include <vector>
#include <cstdio>

namespace Celofan {

    extern int decodePNG(std::vector<unsigned char> &out_image, unsigned long &image_width, unsigned long &image_height,
                         const unsigned char *in_png, size_t in_size, bool convert_to_rgba32 = true);

}

#endif //CELOFAN_PICOPNG_H
