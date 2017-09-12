#ifndef CELOFAN_GLSLPROGRAM_H
#define CELOFAN_GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

namespace Celofan {

    class GLSLProgram {
    public:
        GLSLProgram();

        ~GLSLProgram();

        void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

        void linkShaders();

        void addAttribute(const std::string &attributeName);

        GLint getUniformLocation(const std::string &uniformName);

        void use();

        void unuse();

    private:
        void compileShader(const std::string &filePath, GLuint shaderID);

        GLint _numAttributes;

        GLuint _programID;
        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;

    };

}


#endif //CELOFAN_GLSLPROGRAM_H
