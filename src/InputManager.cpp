#include "InputManager.hpp"

float InputManager::mouseLastX = 0;
float InputManager::mouseLastY = 0;
float InputManager::mouseX = 0;
float InputManager::mouseY = 0;
std::map<int, bool> InputManager::keyDownStates;

void InputManager::setMousePos(float x, float y) {
  mouseLastX = mouseX;
  mouseLastY = mouseY;

  mouseX = x;
  mouseY = y;
}

void InputManager::setKeyState(int key, int state) {
    keyDownStates[key] = state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 InputManager::getMousePosition() {
  return glm::vec2(mouseLastX, mouseLastY);
}

glm::vec2 InputManager::getMouseDelta() {
  return glm::vec2(mouseX - mouseLastX, mouseY - mouseLastY);
}

bool InputManager::isKeyDown(int key) {
  // If key is defined AND down
  return keyDownStates.count(key) && keyDownStates[key];
}

