#include "Scene.h"

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    for (Entity* e : this->entities) {
        delete e;
    }
}

void Scene::update(float dt)
{
    for (Entity* e : this->entities) {
        e->update(dt);
    }
}

void Scene::draw()
{
    for (Entity* e : this->entities) {
        e->draw(this->camera);
    }
}
