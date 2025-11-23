#ifdef DEBUG

#include <pch.h>
#include "graphics/3d/modelInstance.h"
#include "gyroscope_scene.h"
#include "gyroscope.h"

namespace scene {

    GyroscopeScene::GyroscopeScene() {
        auto model = m_modelManager.GetModel("gyroscope.cbdat");
        graphics::ModelInstance modelInstance(model);
        m_entities.emplace_back(std::make_unique<Gyroscope>(modelInstance));
    }

}

#endif // DEBUG
