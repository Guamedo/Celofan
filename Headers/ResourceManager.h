#ifndef CELOFAN_RESOURCEMANAGER_H
#define CELOFAN_RESOURCEMANAGER_H

#include "TextureCache.h"

namespace Celofan {

    class ResourceManager {
    public:
        static GLTexture glTexture(std::string filePath);

    private:
        static TextureCache _textureCache;
    };

}
#endif //CELOFAN_RESOURCEMANAGER_H
