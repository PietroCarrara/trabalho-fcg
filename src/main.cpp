#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <map>
#include <stack>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#include "matrices.hpp"
#include <glcommon.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include "lowlevel.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "MainGameScene.h"

int main()
{
    GLFWwindow* w = initialize_lowlevel();

    MainGameScene s = MainGameScene();

    Cube c1 = Cube();
    Cube c2 = Cube();
    c2.position = glm::vec3(20, 20, 20);

    s.entities.push_back(&c1);
    s.entities.push_back(&c2);

    // Atualiza delta de tempo
    float current_time = (float)glfwGetTime();
    float delta_t = current_time;
    float prev_time = 0;

    while (programAlive(w) && !InputManager::isKeyDown(GLFW_KEY_ESCAPE))
    {
        // UPDATE:
        update_lowlevel(w);

        s.update(delta_t);

        // DRAW:
        glClearColor(0.2, 0.2, 0.2, 0.2);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Desenha os cubos
        s.draw();

        prev_time = current_time;
        current_time = (float)glfwGetTime();
        delta_t = current_time - prev_time;

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    destroy_lowlevel();
    return 0;
}

void main_goals() {
    // initialize_lowlevel();

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

    // destroy_lowlevel();
}
