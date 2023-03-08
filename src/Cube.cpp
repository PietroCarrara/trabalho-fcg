#include "Cube.hpp"

#include <glcommon.h>
#include "matrices.hpp"

#include "glm/mat4x4.hpp"

static GLuint BuildTriangles();

GLuint Cube::vertexArrayID = 0;

Cube::Cube() {
  if (vertexArrayID == 0) {
    vertexArrayID = BuildTriangles();
  }
}

void Cube::update(float deltaTime) {

}

void Cube::draw(LookAtCamera cam) {
  glm::mat4 model =
      Matrix_Translate(this->position.x, this->position.y, this->position.z) *
      Matrix_Scale(this->scale.x, this->scale.y, this->scale.z) *
      Matrix_Rotate_X(this->rotation.x) *
      Matrix_Rotate_Y(this->rotation.y) *
      Matrix_Rotate_Z(this->rotation.z);

  GraphicsManager::DrawElements(model, cam.getMatrix(), vertexArrayID, GL_TRIANGLES, 36, GL_UNSIGNED_INT);
}

static GLuint BuildTriangles()
{
    GLfloat model_coefficients[] = {
    // Vértices de um cubo
    //    X      Y     Z     W
        -0.5f,  0.0f,  0.5f, 1.0f, // posição do vértice 0
        -0.5f, -1.0f,  0.5f, 1.0f, // posição do vértice 1
         0.5f, -1.0f,  0.5f, 1.0f, // posição do vértice 2
         0.5f,  0.0f,  0.5f, 1.0f, // posição do vértice 3
        -0.5f,  0.0f, -0.5f, 1.0f, // posição do vértice 4
        -0.5f, -1.0f, -0.5f, 1.0f, // posição do vértice 5
         0.5f, -1.0f, -0.5f, 1.0f, // posição do vértice 6
         0.5f,  0.0f, -0.5f, 1.0f, // posição do vértice 7
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

    GLfloat color_coefficients[] = {
    // Cores dos vértices do cubo
        //  R     G     B     A
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 0
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 1
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 2
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 3
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 4
        1.0f, 0.5f, 0.0f, 1.0f, // cor do vértice 5
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 6
        0.0f, 0.5f, 1.0f, 1.0f, // cor do vértice 7
    };
    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
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
