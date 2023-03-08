#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "matrices.hpp"

class Camera {
public:
    virtual glm::mat4 getMatrix();
};


class LookAtCamera {
public:
    glm::vec3 focus;
    float rotX = 0, rotY = 0;
    float distance = 3.5;

    LookAtCamera(glm::vec3 lookAt);

    glm::mat4 getMatrix();
};

class FreeCamera {
};

#endif // CAMERA_HPP
