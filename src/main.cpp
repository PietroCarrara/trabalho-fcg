#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <map>
#include <stack>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include "matrices.h"
#include "lowlevel.hpp"
#include "InputManager.hpp"

// Declaração de várias funções utilizadas em main().  Essas estão definidas
// logo após a definição de main() neste arquivo.
void DrawCube(); // Desenha um cubo

int main()
{
    initialize_lowlevel();

    GLuint vertex_array_object_id = BuildTriangles();
    GLint model_uniform           = glGetUniformLocation(g_GpuProgramID, "model"); // Variável da matriz "model"
    GLint view_uniform            = glGetUniformLocation(g_GpuProgramID, "view"); // Variável da matriz "view" em shader_vertex.glsl
    GLint projection_uniform      = glGetUniformLocation(g_GpuProgramID, "projection"); // Variável da matriz "projection" em shader_vertex.glsl

    float g_CameraTheta = 0.0f; // Ângulo no plano ZX em relação ao eixo Z
    float g_CameraPhi = 0.0f;   // Ângulo em relação ao eixo Y
    float g_CameraDistance = 3.5f; // Distância da câmera para a origem

    while (programAlive() && !InputManager::isKeyDown(GLFW_KEY_ESCAPE))
    {
        // UPDATE:
        update_lowlevel();
        if (InputManager::isKeyDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            // Deslocamento do cursor do mouse em x e y de coordenadas de tela!
            float dx = InputManager::getMouseDelta().x;
            float dy = InputManager::getMouseDelta().y;

            // Atualizamos parâmetros da câmera com os deslocamentos
            g_CameraTheta -= 0.01f*dx;
            g_CameraPhi   += 0.01f*dy;

            // Em coordenadas esféricas, o ângulo phi deve ficar entre -pi/2 e +pi/2.
            float phimax = 3.141592f/2;
            float phimin = -phimax;

            if (g_CameraPhi > phimax)
                g_CameraPhi = phimax;

            if (g_CameraPhi < phimin)
                g_CameraPhi = phimin;
        }

        // DRAW:
        glClearColor(100/1.0f, 149/1.0f, 237/1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUseProgram(g_GpuProgramID);
        glBindVertexArray(vertex_array_object_id);

        float r = g_CameraDistance;
        float y = r*sin(g_CameraPhi);
        float z = r*cos(g_CameraPhi)*cos(g_CameraTheta);
        float x = r*cos(g_CameraPhi)*sin(g_CameraTheta);
        glm::vec4 camera_position_c  = glm::vec4(x,y,z,1.0f); // Ponto "c", centro da câmera
        glm::vec4 camera_lookat_l    = glm::vec4(0.0f,0.0f,0.0f,1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada
        glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f); // Vetor "up" fixado para apontar para o "céu" (eito Y global)
        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);

        glm::mat4 projection;

        float nearplane = -0.1f;  // Posição do "near plane"
        float farplane  = -40.0f; // Posição do "far plane"

        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, GraphicsManager::getScreenRatio(), nearplane, farplane);

        glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(view));
        glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection));

        // Desenha o cubo
        glm::mat4 model = Matrix_Identity();
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        DrawCube();

        // Desenha o cubo 2
        model = Matrix_Translate(20, 20, 20);
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        DrawCube();

        // Pedimos para OpenGL desenhar linhas com largura de 10 pixels.
        glLineWidth(10.0f);

        glDrawElements(
            g_VirtualScene["axes"].rendering_mode,
            g_VirtualScene["axes"].num_indices,
            GL_UNSIGNED_INT,
            (void*)g_VirtualScene["axes"].first_index
        );

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void main_goals() {
    initialize_lowlevel();

    // World world;
    // Scene firstScene;

    // Cube cube1, cube2;
    // cube2.position = vec3(2, 2, 2);

    // firstScene.add(cube1);
    // firstScene.add(cube2);

    // while (world.notEnded()) {
    //     update_lowlevel();
    //     world.update();
    //     world.draw();
    // }
    // world.destroy();

    destroy_lowlevel();
}

// Função que desenha um cubo com arestas em preto, definido dentro da função BuildTriangles().
void DrawCube()
{
    glDrawElements(
        g_VirtualScene["cube_faces"].rendering_mode, // Veja slides 182-188 do documento Aula_04_Modelagem_Geometrica_3D.pdf
        g_VirtualScene["cube_faces"].num_indices,    //
        GL_UNSIGNED_INT,
        (void*)g_VirtualScene["cube_faces"].first_index
    );

    // TODO: Remover
    glLineWidth(4.0f);
    glDrawElements(
        g_VirtualScene["axes"].rendering_mode,
        g_VirtualScene["axes"].num_indices,
        GL_UNSIGNED_INT,
        (void*)g_VirtualScene["axes"].first_index
    );
}
