#include <pch.h>
#include "gyroscope_scene.h"
#include "graphics/model/modelInstance.h"
#include "gyroscope.h"

namespace scene {

    GyroscopeScene::GyroscopeScene() {
        auto model = m_modelManager.GetModel("gyroscope.cbdat");
        graphics::ModelInstance modelInstance(model);
        m_entities.emplace_back(std::make_unique<Gyroscope>(modelInstance));
    }

}
