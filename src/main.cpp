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
#include <utilities.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lowlevel.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "MainGameScene.h"

int main()
{
    srand(time(NULL));
    GLFWwindow* w = initialize_lowlevel();
    update_lowlevel(w);

    MainGameScene s = MainGameScene();

    while (programAlive(w) && !InputManager::isKeyDown(GLFW_KEY_ESCAPE))
    {
        // UPDATE:
        float deltaTime = update_lowlevel(w);
        s.update(deltaTime);

        // DRAW:
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        s.draw();

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    destroy_lowlevel();
    return 0;
}
