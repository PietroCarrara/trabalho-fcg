#ifndef GRAPHICS_MANAGER_HPP
#define GRAPHICS_MANAGER_HPP

#include <sstream>
#include <fstream>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glcommon.h>

#include "matrices.hpp"

class GraphicsManager {
private:
    static float screenRatio;
    static glm::mat4 perspectiveProjection;

    static GLuint shaderID;
    static GLint modelUniform;
    static GLint viewUniform;
    static GLint projectionUniform;

    static float fov;
    static float near;
    static float far;

public:
    static void init();
    static void setScreenRatio(float r);

    static void DrawElements(glm::mat4 model, glm::mat4 view, GLuint vertexArrayID, GLenum drawMode, GLsizei elCount, GLenum type);
};

#endif