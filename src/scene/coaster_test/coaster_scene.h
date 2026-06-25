#ifdef DEBUG

#ifndef COASTER_SCENE_H
#define COASTER_SCENE_H

#include "scene/scene.h"

namespace scene {

    class CoasterScene : public Scene {
    public:
        CoasterScene();
    };

    class PlaceHolderModel : public Entity {
    public:
        PlaceHolderModel(graphics::ModelInstance model)
            : Entity(model) {};

        virtual void Update(float /*timestep*/) override {};

    };

}

#endif // COASTER_SCENE_H

#endif // DEBUG
