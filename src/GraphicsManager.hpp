#ifndef GRAPHICS_MANAGER_HPP
#define GRAPHICS_MANAGER_HPP

class GraphicsManager {
private:
    static float screenRatio;

public:
    static void setScreenRatio(float r) {
        screenRatio = r;
    }

    static float getScreenRatio() {
        return screenRatio;
    }
};

float GraphicsManager::screenRatio = 1;

#endif
