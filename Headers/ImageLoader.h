#ifndef CELOFAN_IMAGELOADER_H
#define CELOFAN_IMAGELOADER_H

#include <string>
#include "GLTexture.h"

namespace Celofan {

    class ImageLoader {
    public:
        static GLTexture loadPNG(std::string filePath);
    };

}

#endif //CELOFAN_IMAGELOADER_H
