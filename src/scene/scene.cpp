#include <pch.h>
#include "scene.h"

#include "settings.h"
#include "utils/logger.h"

namespace scene {

    Scene::Scene()
        : m_camera({0, 0, 1280, 720}) {
        LOG_DEBUG("Constructor: Scene");
        m_frames.emplace_back(std::make_unique<UI::SettingsMenu>());
    }

    void Scene::Update(float timestep) {
        m_camera.Update(timestep);

        for (auto& entity : m_entities) {
            entity->Update(timestep);
        }
    }

}
