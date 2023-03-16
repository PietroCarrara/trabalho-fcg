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
#include "MainGameScene.h"

int main()
{
    srand(time(NULL));
    GLFWwindow* w = initialize_lowlevel();

    MainGameScene s = MainGameScene();

    // Atualiza delta de tempo
    float current_time = (float)glfwGetTime();
    float delta_t = current_time;
    float prev_time = 0;

    update_lowlevel(w);

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
