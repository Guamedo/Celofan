#ifndef CELOFAN_GLTEXTURE_H
#define CELOFAN_GLTEXTURE_H
#include <GL/glew.h>

namespace Celofan {

    struct GLTexture {
        GLuint id;
        int width;
        int height;
    };

}

#endif //CELOFAN_GLTEXTURE_H
