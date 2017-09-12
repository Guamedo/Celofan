#ifndef CELOFAN_VERTEX_H
#define CELOFAN_VERTEX_H

#include <GL/glew.h>

namespace Celofan {

    struct Position {
        GLfloat x;
        GLfloat y;
    };

    struct Color {
        Color(){

        }
        Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A){
            r = R;
            g = G;
            b = B;
            a = A;
        }
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV {
        GLfloat u;
        GLfloat v;
    };

    struct Vertex {
        Position position;
        Color color;
        UV uv;

        void setPosition(GLfloat x, GLfloat y) {
            position.x = x;
            position.y = y;
        }

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setUV(GLfloat u, GLfloat v) {
            uv.u = u;
            uv.v = v;
        }
    };

}
#endif //CELOFAN_VERTEX_H
