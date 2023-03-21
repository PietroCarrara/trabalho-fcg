#include "Skybox.h"

#include <vector>
#include <string>

#include "stb_image.h"
#include "GraphicsManager.hpp"

static GLuint loadCube();

Skybox::Skybox() {
  this->vbo = loadCube();

  std::vector<const char*> files = {
    "../../assets/skybox/right.png",
    "../../assets/skybox/left.png",
    "../../assets/skybox/up.png",
    "../../assets/skybox/down.png",
    "../../assets/skybox/back.png",
    "../../assets/skybox/front.png",
  };
  this->texture = GraphicsManager::loadCubeMap(files);
}

void Skybox::draw(Camera *c) {
  GraphicsManager::DrawSkybox(c, this->texture, this->vbo);
}

static GLuint loadCube()
{
    GLfloat model_coefficients[] = {
    // Vértices de um cubo
    //    X      Y     Z     W
      -1.0f,  1.0f,  1.0f, 1.0f, // posição do vértice 0
      -1.0f, -1.0f,  1.0f, 1.0f, // posição do vértice 1
       1.0f, -1.0f,  1.0f, 1.0f, // posição do vértice 2
       1.0f,  1.0f,  1.0f, 1.0f, // posição do vértice 3
      -1.0f,  1.0f, -1.0f, 1.0f, // posição do vértice 4
      -1.0f, -1.0f, -1.0f, 1.0f, // posição do vértice 5
       1.0f, -1.0f, -1.0f, 1.0f, // posição do vértice 6
       1.0f,  1.0f, -1.0f, 1.0f, // posição do vértice 7
    };

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);

    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);

    glBindVertexArray(vertex_array_object_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(model_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(model_coefficients), model_coefficients);

    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint indices[] = {
        0, 1, 2, // triângulo 1
        7, 6, 5, // triângulo 2
        3, 2, 6, // triângulo 3
        4, 0, 3, // triângulo 4
        4, 5, 1, // triângulo 5
        1, 5, 6, // triângulo 6
        0, 2, 3, // triângulo 7
        7, 5, 4, // triângulo 8
        3, 6, 7, // triângulo 9
        4, 3, 7, // triângulo 10
        4, 1, 0, // triângulo 11
        1, 6, 2, // triângulo 12
    };

    // Criamos um buffer OpenGL para armazenar os índices acima
    GLuint indices_id;
    glGenBuffers(1, &indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glBindVertexArray(0);
    return vertex_array_object_id;
}
