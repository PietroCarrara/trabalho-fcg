#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "matrices.h"

class Camera {
public:
    virtual glm::mat4 getMatrix();
};


class LookAtCamera {
private:
    glm::vec3 focus;
    float rotX, rotY;
    float distance;
public:
    void setFocusPoint(glm::vec3 focus) {
        this->focus = focus;
    }
    void setRotationX(float r) {
        this->rotX = r;
    }
    void setRotationY(float r) {
        const float MAX = 3.141592f/2;
        if (r > MAX) {
            r = MAX;
        } else if (r < -MAX) {
            r =- MAX;
        }

        this->rotY = r;
    }
    void setDistance(float d) {
        this->distance = d;
    }

    float getRotationX() {
        return this->rotX;
    }
    float getRotationY() {
        return this->rotY;
    }
    float getDistance() {
        return this->distance;
    }

    glm::mat4 getMatrix() {
        float r = this->distance;
        float y = r*sin(this->rotY);
        float z = r*cos(this->rotY)*cos(this->rotX);
        float x = r*cos(this->rotY)*sin(this->rotX);
        glm::vec4 camera_position_c  = glm::vec4(x,y,z,1.0f); // Ponto "c", centro da câmera
        glm::vec4 camera_lookat_l    = glm::vec4(0.0f,0.0f,0.0f,1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f); // Vetor "up" fixado para apontar para o "céu" (eito Y global)
        return Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);
    }
};

class FreeCamera: Camera {
};

#endif // CAMERA_HPP
