#ifdef DEBUG

#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "scene/entity.h"

namespace scene {

    class Gyroscope : public Entity {

    public:
        Gyroscope(graphics::ModelInstance model)
            : Entity(model) {};

        virtual void Update(float timestep) override;

    };

}

#endif // GYROSCOPE_H

#endif // DEBUG
