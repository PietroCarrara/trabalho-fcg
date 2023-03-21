#ifndef SKYBOX_ENTITY_H
#define SKYBOX_ENTITY_H

#include <glcommon.h>

#include "Camera.hpp"

class Skybox  {
  private:
    GLuint vbo;
    GLuint texture;

  public:
    Skybox();

    void draw(Camera *c);
};

#endif