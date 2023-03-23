#ifndef CAMERAALTERNATORENTITY_H
#define CAMERAALTERNATORENTITY_H

#include "Entity.h"
#include "Player.h"
#include "PageEntity.h"
#include "Camera.hpp"

class CameraAlternatorEntity : public Entity, public Camera
{
    private:
        int currentObj = 0;
        Player* player;
        std::vector<PageEntity*> pages;
        LookAtCamera lookAtCam = LookAtCamera(glm::vec3(0));

    public:
        CameraAlternatorEntity(Player* p, std::vector<PageEntity*> pages);

        void update(float dt);
        void draw(Camera* c);

        glm::mat4 getMatrix();
        glm::vec4 getViewVec();
};

#endif // CAMERAALTERNATORENTITY_H
