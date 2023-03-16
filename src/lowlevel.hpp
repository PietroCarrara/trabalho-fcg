#ifndef LOWLEVEL_H
#define LOWLEVEL_H

#include <glcommon.h>

bool programAlive(GLFWwindow* w);

GLFWwindow* initialize_lowlevel();
float update_lowlevel(GLFWwindow*);
void destroy_lowlevel();

#endif
