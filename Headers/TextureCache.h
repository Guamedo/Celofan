#ifndef CELOFAN_TEXTURECACHE_H
#define CELOFAN_TEXTURECACHE_H

#include <map>
#include <string>

#include "GLTexture.h"

namespace Celofan {

    class TextureCache {
    public:
        TextureCache();

        ~TextureCache();

        GLTexture getTexture(std::string filePath);

    private:
        std::map<std::string, GLTexture> _textureMap;
    };

}

#endif //CELOFAN_TEXTURECACHE_H
