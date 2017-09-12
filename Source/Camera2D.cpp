#include "../Headers/Camera2D.h"

namespace Celofan {

    Camera2D::Camera2D() : _position(0.0f, 0.0f),
                           _scale(1.0f),
                           _needsMatrixUpdate(true),
                           _cameraMatrix(1.0f),
                           _screenWidth(500),
                           _screenHeight(500),
                           _orthoMatrix(1.0f) {

    }

    Camera2D::~Camera2D(){

    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.0f, (float) _screenWidth, 0.0f, (float) _screenHeight);
    }

    void Camera2D::update() {

        if (_needsMatrixUpdate) {
            glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y  + _screenHeight/2, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);

            glm::vec3 scale(_scale, _scale, 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

            _needsMatrixUpdate = false;
        }
    }

    glm::vec2 Camera2D::screenToWorld(glm::vec2 screenCoords) {
        screenCoords.y = _screenHeight - screenCoords.y;
        screenCoords -= glm::vec2(_screenWidth/2, _screenHeight/2);
        screenCoords /= _scale;
        screenCoords += _position;
        return screenCoords;
    }

    void Camera2D::setPositon(const glm::vec2 &newPositon) {
        _position = newPositon;
        _needsMatrixUpdate = true;
    }

    void Camera2D::setScale(float newScale) {
        _scale = newScale;
        _needsMatrixUpdate = true;
    }

    const glm::vec2 &Camera2D::getPositon() const {
        return _position;
    }

    float Camera2D::getScale() const {
        return _scale;
    }

    const glm::mat4 &Camera2D::getCameraMatrix() const {
        return _cameraMatrix;
    }

}