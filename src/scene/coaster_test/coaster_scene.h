#ifdef DEBUG

#ifndef COASTER_SCENE_H
#define COASTER_SCENE_H

#include "scene/scene.h"

namespace scene {

    class CoasterScene : public Scene {
    public:
        CoasterScene();

        virtual void Update(float timestep) override;

    private:
        float timer = 0.f;
        int clock = 1;
    };

}

#endif // COASTER_SCENE_H

#endif // DEBUG
