#ifndef CAMERAALTERNATORENTITY_H
#define CAMERAALTERNATORENTITY_H

#include <list>

#include "Entity.h"
#include "Player.h"
#include "PageEntity.h"
#include "Camera.hpp"

class CameraAlternatorEntity : public Entity, public Camera
{
    private:
        unsigned int currentObj = 0;
        Player* player;
        std::list<PageEntity*> pages;
        LookAtCamera lookAtCam = LookAtCamera(glm::vec3(0));

    public:
        CameraAlternatorEntity(Player* p, std::list<PageEntity*> pages);

        void update(float dt);
        void onPageRemoved();

        glm::mat4 getMatrix();
        glm::vec4 getViewVec();
};

#endif // CAMERAALTERNATORENTITY_H
