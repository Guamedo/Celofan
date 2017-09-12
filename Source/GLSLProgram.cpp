#include <fstream>
#include <vector>
#include <iostream>

#include "../Headers/GLSLProgram.h"
#include "../Headers/Errors.h"

namespace Celofan {

    GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {

    }

    GLSLProgram::~GLSLProgram() {

    }

    void
    GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath) {

        //Create the program object
        _programID = glCreateProgram();

        //Create the vertex shader with OpenGL
        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (_vertexShaderID == 0) {
            fatalError("Vertex shader failed to be created");
        }

        //Create the fragment shader with OpenGL
        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (_fragmentShaderID == 0) {
            fatalError("Fragment shader failed to be created");
        }

        compileShader(vertexShaderFilePath, _vertexShaderID);
        compileShader(fragmentShaderFilePath, _fragmentShaderID);
    }

    void GLSLProgram::linkShaders() {

        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);

        glLinkProgram(_programID);

        // Error checking
        GLint isLinked = 0;
        glGetProgramiv(_programID, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

            //We don't need the program anymore.
            glDeleteProgram(_programID);
            //Don't leak shaders either.
            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);

            //Use the infoLog as you see fit.
            fprintf(stderr, &(infoLog[0]));
            //std::printf("%s\n", &(infoLog[0]));
            fatalError("Error linking the shaders to the program");

        }

        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID, _fragmentShaderID);
    }


    void GLSLProgram::addAttribute(const std::string &attributeName) {
        glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
        GLint location = glGetUniformLocation(_programID, uniformName.c_str());
        if (location == GL_INVALID_INDEX) {
            fatalError("Uniform " + uniformName + " not found in shader");
        }
        return location;
    }

    void GLSLProgram::use() {
        glUseProgram(_programID);
        for (int i = 0; i < _numAttributes; i++) {
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse() {
        glUseProgram(0);
        for (int i = 0; i < _numAttributes; i++) {
            glDisableVertexAttribArray(i);
        }
    }

    void GLSLProgram::compileShader(const std::string &filePath, GLuint shaderID) {
        //Open the shader file
        std::ifstream vertexfile(filePath);
        if (vertexfile.fail()) {
            perror(filePath.c_str());
            fatalError("Failed to open " + filePath);
        }

        //Read the content of the shader file and store it in a string
        std::string fileContents;
        std::string line;

        while (std::getline(vertexfile, line)) {
            fileContents += line + "\n";
        }
        vertexfile.close();

        //Compile the shader
        const char *contentsPtr = fileContents.c_str();
        glShaderSource(shaderID, 1, &contentsPtr, nullptr);

        glCompileShader(shaderID);

        //Error checking
        GLint success = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(shaderID); // Don't leak the shader.

            fprintf(stderr, &(errorLog[0]));
            //printf("%s\n", &(errorLog[0]));
            fatalError("Failed to compile the " + filePath + " shader");
        }
    }

}