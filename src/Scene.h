#ifndef SCENE_H
#define SCENE_H

#include <list>

#include "Camera.hpp"
#include "Entity.h"

class Scene
{
    protected:
        std::list<Entity*> entities;

    public:
        Camera* camera;

        Scene();
        virtual ~Scene();

        virtual void update(float dt);
        virtual void draw();

        template<typename T>
        T* addEntity(T* e) {
            this->entities.push_back(e);
            return e;
        }
};

#endif // SCENE_H
