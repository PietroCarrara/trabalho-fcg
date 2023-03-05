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
#include "Camera.hpp"
#include "Cube.hpp"

// Declaração de várias funções utilizadas em main().  Essas estão definidas
// logo após a definição de main() neste arquivo.
void DrawCube(); // Desenha um cubo

int main()
{
    initialize_lowlevel();

    LookAtCamera cam = LookAtCamera();
    cam.setDistance(3.5);
    cam.setRotationX(0);
    cam.setRotationY(0);

    Cube c1 = Cube();
    Cube c2 = Cube();
    c2.position = glm::vec3(20, 20, 20);

    while (programAlive() && !InputManager::isKeyDown(GLFW_KEY_ESCAPE))
    {
        // UPDATE:
        update_lowlevel();

        // Update camera!
        if (InputManager::isKeyDown(GLFW_MOUSE_BUTTON_LEFT))
        {
            // Deslocamento do cursor do mouse em x e y de coordenadas de tela!

            float dx = InputManager::getMouseDelta().x;
            float dy = InputManager::getMouseDelta().y;

            // Atualizamos parâmetros da câmera com os deslocamentos
            cam.setRotationX(cam.getRotationX() - 0.01*dx);
            cam.setRotationY(cam.getRotationY() + 0.01*dy);
        }

        // DRAW:
        glClearColor(100/1.0f, 149/1.0f, 237/1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Desenha o cubo
        glm::mat4 model = Matrix_Identity();
        c1.draw(cam);

        // Desenha o cubo 2
        model = Matrix_Translate(20, 20, 20);
        c2.draw(cam);

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

}
