#ifndef CELOFAN_SPRITE_H
#define CELOFAN_SPRITE_H

#include <GL/glew.h>
#include <string>

#include "GLTexture.h"

namespace Celofan {

    class Sprite {
    public:
        Sprite();

        ~Sprite();

        void init(GLfloat x, GLfloat y, GLfloat width, GLfloat height, std::string texturePath);

        void draw();

    private:
        GLfloat _x;
        GLfloat _y;
        GLfloat _width;
        GLfloat _height;

        //Identifier of the vertex buffer of the sprite
        GLuint _vboID;

        GLTexture _texture;
    };

}

#endif //CELOFAN_SPRITE_H
