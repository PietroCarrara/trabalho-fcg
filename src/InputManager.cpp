#include "InputManager.hpp"

#include <cstdio>

#include "ObjEntity.h"

void assertExists(int, std::map<int, bool>);

float InputManager::mouseLastX = 0;
float InputManager::mouseLastY = 0;
float InputManager::mouseX = 0;
float InputManager::mouseY = 0;
std::map<int, bool> InputManager::prevKeyDownStates;
std::map<int, bool> InputManager::keyDownStates;

void InputManager::setMousePos(float x, float y) {
  mouseLastX = mouseX;
  mouseLastY = mouseY;

  mouseX = x;
  mouseY = y;
}

void InputManager::setKeyState(int key, int state) {
    bool down = state == GLFW_PRESS || state == GLFW_REPEAT;

    prevKeyDownStates[key] = keyDownStates[key];
    keyDownStates[key] = down;
}

glm::vec2 InputManager::getMousePosition() {
  return glm::vec2(mouseLastX, mouseLastY);
}

glm::vec2 InputManager::getMouseDelta() {
  return glm::vec2(mouseX - mouseLastX, mouseY - mouseLastY);
}

bool InputManager::isKeyDown(int key) {
  assertExists(key, keyDownStates);
  return keyDownStates[key];
}

bool InputManager::isKeyPressed(int key) {
  assertExists(key, keyDownStates);
  assertExists(key, prevKeyDownStates);
  return !prevKeyDownStates[key] && keyDownStates[key];
}

void assertExists(int key, std::map<int, bool> keys) {
  if (!keys.count(key)) {
    const char* name = glfwGetKeyName(key, 0);
    fprintf(stderr, "Key \"%s\" (code %d) not registered on lowlevel.cpp! Exiting...", name, key);
    exit(1);
  }
}
