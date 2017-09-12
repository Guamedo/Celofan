#include "../Headers/ResourceManager.h"

namespace Celofan {

    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::glTexture(std::string filePath) {
        return _textureCache.getTexture(filePath);
    }
}