#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"
#include "Player.h"
#include "PageEntity.h"
#include "AudioManager.h"

class MenuScene : public Scene
{
    private:
        Player *player;
        PageEntity* playPage;
        PageEntity* quitPage;
        Sound* song;

    public:
        MenuScene();
        ~MenuScene();

        Scene* update(float dt);
};

#endif // MENU_SCENE_H
