#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <map>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

class InputManager {
private:
    static float mouseLastX, mouseLastY, mouseX, mouseY;
    static std::map<int, bool> keyDownStates;

public:
    static void setMousePos(float x, float y) {
        mouseLastX = mouseX;
        mouseLastY = mouseY;

        mouseX = x;
        mouseY = y;
    }

    static void setKeyState(int key, int state) {
        keyDownStates[key] = state == GLFW_PRESS;
    }

    static glm::vec2 getMousePosition() {
        return glm::vec2(mouseLastX, mouseLastY);
    }

    static glm::vec2 getMouseDelta() {
        return glm::vec2(mouseX - mouseLastX, mouseY - mouseLastY);
    }

    static bool isKeyDown(int key) {
        // If key is defined AND down
        return keyDownStates.count(key) && keyDownStates[key];
    }
};

float InputManager::mouseLastX = 0;
float InputManager::mouseLastY = 0;
float InputManager::mouseX = 0;
float InputManager::mouseY = 0;
std::map<int, bool> InputManager::keyDownStates;

#endif // INPUT_MANAGER_HPP
