#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

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
#include "MenuScene.h"

int main()
{
    srand(time(NULL));
    GLFWwindow* w = initialize_lowlevel();
    update_lowlevel(w);

    Scene *s = new MenuScene();
    bool running = true;

    while (running && programAlive(w) && !InputManager::isKeyDown(GLFW_KEY_ESCAPE))
    {
        // UPDATE:
        float deltaTime = update_lowlevel(w);
        Scene* next = s->update(deltaTime);

        // DRAW:
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        s->draw();

        // Switch scenes if needed
        if (s != next) {
            if (next == nullptr) {
                running = false;
            } else {
                delete s;
                s = next;
            }
        }

        glfwSwapBuffers(w);
        glfwPollEvents();
    }
    delete s;

    destroy_lowlevel();
    return 0;
}
