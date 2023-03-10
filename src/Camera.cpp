#include "Camera.hpp"

#include <glcommon.h>

#include "matrices.hpp"

LookAtCamera::LookAtCamera(glm::vec3 lookAt) {
  this->focus = lookAt;
}

glm::mat4 LookAtCamera::getMatrix() {
  float r = this->distance;
  float y = r * sin(this->rotY);
  float z = r * cos(this->rotY) * cos(this->rotX);
  float x = r * cos(this->rotY) * sin(this->rotX);
  glm::vec4 camera_position_c =
      glm::vec4(x, y, z, 1.0f);  // Ponto "c", centro da câmera
  glm::vec4 camera_lookat_l = glm::vec4(
      0.0f, 0.0f, 0.0f,
      1.0f);  // Ponto "l", para onde a câmera (look-at) estará sempre olhando
  glm::vec4 camera_view_vector =
      camera_lookat_l - camera_position_c;  // Vetor "view", sentido para onde a
                                            // câmera está virada
  glm::vec4 camera_up_vector = glm::vec4(
      0.0f, 1.0f, 0.0f,
      0.0f);  // Vetor "up" fixado para apontar para o "céu" (eito Y global)
  return Matrix_Camera_View(camera_position_c, camera_view_vector,
                            camera_up_vector);
}

glm::vec4 LookAtCamera::getViewVec() {
    return glm::vec4(
        cos(this->rotY)*sin(this->rotX),
        -sin(this->rotY),
        cos(this->rotY)*cos(this->rotX),
        0.0f
    );
}

glm::mat4 FreeCamera::getMatrix() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;

    glm::vec4 cam_view = this->getViewVec();

    glm::vec4 up = glm::vec4(0, 1, 0, 0);

    return Matrix_Camera_View(glm::vec4(x, y, z, 1.0f), cam_view, up);
}


glm::vec4 FreeCamera::getViewVec() {
    return glm::vec4(
        cos(this->rotY)*sin(this->rotX),
        -sin(this->rotY),
        cos(this->rotY)*cos(this->rotX),
        0.0f
    );
}
