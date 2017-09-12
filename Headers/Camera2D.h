#ifndef BENGINE_CAMERA2D_H
#define BENGINE_CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Celofan {

    class Camera2D {
    public:
        Camera2D();

        ~Camera2D();

        void init(int screenWidth, int screenHeight);

        void update();

        glm::vec2 screenToWorld(glm::vec2 screenCoords);

        void setPositon(const glm::vec2 &newPositon);

        void setScale(float newScale);

        const glm::vec2 &getPositon() const;

        float getScale() const;

        const glm::mat4 &getCameraMatrix() const;

    private:
        int _screenWidth, _screenHeight;
        bool _needsMatrixUpdate;
        float _scale;
        glm::vec2 _position;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
    };

}
#endif //BENGINE_CAMERA2D_H