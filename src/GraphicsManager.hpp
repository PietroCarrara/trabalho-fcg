#ifndef GRAPHICS_MANAGER_HPP
#define GRAPHICS_MANAGER_HPP

#include <sstream>
#include <fstream>
#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glcommon.h>

#include "matrices.hpp"
#include "Camera.hpp"

class GraphicsManager {
private:
    static float screenRatio;
    static glm::mat4 perspectiveProjection;

    static GLuint shaderID;
    static GLint modelUniform;
    static GLint viewUniform;
    static GLint projectionUniform;
    static GLint viewVecUniform;
    static GLint bboxMinUniform;
    static GLint bboxMaxUniform;
    static GLint colorTextureUniform;
    static GLint timeUniform;

    static float fov;
    static float nearPlane;
    static float farPlane;

public:
    static void init();
    static void setScreenRatio(float r);
    static void setTime(float t);

    static void DrawElements(glm::mat4 model, Camera* cam, glm::vec3 bboxMin, glm::vec3 bboxMax, GLuint texture, GLuint vertexArrayID, GLenum drawMode, GLsizei elCount, GLenum type, void* firstIndex = 0);
};

#endif
