#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <map>
#include <glm/vec2.hpp>
#include <glcommon.h>

class InputManager {
private:
    static float mouseLastX, mouseLastY, mouseX, mouseY;
    static std::map<int, bool> prevKeyDownStates;
    static std::map<int, bool> keyDownStates;

public:
    static void setMousePos(float x, float y);
    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseDelta();

    static bool isKeyDown(int key);
    static bool isKeyPressed(int key);
    static void setKeyState(int key, int state);
};

#endif // INPUT_MANAGER_HPP
