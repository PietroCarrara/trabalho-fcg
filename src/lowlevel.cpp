#include "lowlevel.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <limits>
#include <map>
#include <sstream>
#include <stack>
#include <string>

#include <glcommon.h>

#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "matrices.hpp"
#include "utils.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
void ErrorCallback(int error, const char* description);

void update_lowlevel(GLFWwindow* w) {
  double x, y;
  glfwGetCursorPos(w, &x, &y);
  InputManager::setMousePos((float)x, (float)y);
}

void destroy_lowlevel() {
  glfwTerminate();
}

GLFWwindow* initialize_lowlevel() {
  int success = glfwInit();
  if (!success) {
  fprintf(stderr, "ERROR: glfwInit() failed.\n");
  std::exit(EXIT_FAILURE);
  }
  glfwSetErrorCallback(ErrorCallback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(800, 800, "Hello, World!", NULL, NULL);
  if (!window) {
  glfwTerminate();
  fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
  std::exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, KeyCallback);
  glfwSetMouseButtonCallback(window, MouseButtonCallback);
  // glfwSetCursorPosCallback(window, CursorPosCallback);
  glfwSetScrollCallback(window, ScrollCallback);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

  glfwSetWindowSize(window, 800, 800);  // Forçamos a chamada do callback acima,
                    // para definir g_ScreenRatio.
  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  GraphicsManager::init();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  double x, y;
  glfwGetCursorPos(window, &x, &y);
  InputManager::setMousePos((float)x, (float)y);

  return window;
}

bool programAlive(GLFWwindow* w) {
  return !glfwWindowShouldClose(w);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  GraphicsManager::setScreenRatio(width / (float)height);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  InputManager::setKeyState(button, action);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod) {
  InputManager::setKeyState(key, action);
}

void ErrorCallback(int error, const char* description) {
  fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
