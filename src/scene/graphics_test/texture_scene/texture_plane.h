#ifdef DEBUG

#ifndef TEXTURE_PLANE_H
#define TEXTURE_PLANE_H

#include "scene/entity.h"

namespace scene {

    class TexturePlane : public Entity {

    public:
        TexturePlane(graphics::ModelInstance model)
            : Entity(model) {};

        virtual void Update(float timestep) override;

    };

}

#endif // TEXTURE_PLANE_H

#endif // DEBUG
