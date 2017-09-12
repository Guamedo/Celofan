#ifndef CELOFAN_INPUTMANAGER_H
#define CELOFAN_INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace Celofan {

    class InputManager {
    public:
        InputManager();
        ~InputManager();

        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);

        void setMouseCoords(float x, float y);

        bool isKeyPress(unsigned int keyID);

        //getters
        glm::vec2 getMouseCorrds();

    private:
        std::unordered_map<unsigned int, bool> _keyMap;
        glm::vec2 _mouseCoords;

    };

}
#endif //CELOFAN_INPUTMANAGER_H
