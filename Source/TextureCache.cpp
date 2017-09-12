#include <iostream>
#include "../Headers/TextureCache.h"
#include "../Headers/ImageLoader.h"

namespace Celofan {

    TextureCache::TextureCache() {

    }

    TextureCache::~TextureCache() {

    }

    GLTexture TextureCache::getTexture(std::string filePath) {

        auto it = _textureMap.find(filePath);
        if (it == _textureMap.end()) {
            GLTexture newTexture = ImageLoader::loadPNG(filePath);

            _textureMap.insert(make_pair(filePath, newTexture));

            std::cout << "Loaded Texture\n";
            return newTexture;
        }

        std::cout << "Used Cached Texture\n";
        return it->second;
    }

}