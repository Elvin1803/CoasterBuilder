#include <pch.h>
#include "scene.h"

#include "modelManager.h"
#include "utils/logger.h"

namespace scene {

    Scene::Scene()
        // Fixme: camera dimensions
        : m_camera(graphics::ViewportRect{0, 0, 1280, 720}){
    }

    void Scene::Update(float timestep) {
        m_camera.Update(timestep);

        for (auto& entity : m_entities) {
            entity->Update(timestep);
        }
    }

}
