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
        CurveData data{10, 0, 0, 0};

        glm::vec3 camPos{15, 4, 25};
        glm::vec3 camRot{0, 0, 0};
    };

}

#endif // COASTER_SCENE_H

#endif // DEBUG
