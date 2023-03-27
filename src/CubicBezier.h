#ifndef CUBICBEZIER_H
#define CUBICBEZIER_H

#include <glm/vec3.hpp>

class CubicBezier
{
    private:
        float direction = 1;
        bool loop;
        float timer = 0;
        float duration;
        glm::vec3 p1;
        glm::vec3 p2;
        glm::vec3 p3;
        glm::vec3 p4;

    public:
        CubicBezier(float duration, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, bool loop = true);

        void update(float dt);
        glm::vec3 getPoint();
};

#endif // CUBICBEZIER_H
