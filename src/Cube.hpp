#ifndef CUBE_HPP
#define CUBE_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glcommon.h>

#include "matrices.hpp"
#include "GraphicsManager.hpp"
#include "Camera.hpp"
#include "Entity.h"

class Cube : public Entity {
private:
    static GLuint vertexArrayID;

public:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    Cube();

    void update(float deltaTime);
    void draw(Camera* c);
};

#endif // CUBE_HPP
