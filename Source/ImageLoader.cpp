//
// Created by GPA on 04/08/2017.
//

#include "../Headers/ImageLoader.h"
#include "../Headers/picoPNG.h"
#include "../Headers/IOManager.h"
#include "../Headers/Errors.h"

namespace Celofan {

    GLTexture ImageLoader::loadPNG(std::string filePath) {

        // Init all the values of the GLTextue struct to 0
        GLTexture texture = {};

        std::vector<unsigned char> in;
        std::vector<unsigned char> out;

        unsigned long width, height;

        if (!IOManager::readFileToBuffer(filePath, in)) {
            fatalError("Filed to load " + filePath + " image");
        }

        int error;
        if ((error = decodePNG(out, width, height, in.data(), in.size())) != 0) {
            fatalError("decodePNG failed with error: " + error);
        }

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        texture.width = (int) width;
        texture.height = (int) height;

        return texture;
    }

}