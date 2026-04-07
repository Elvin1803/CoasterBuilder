#include <pch.h>
#include "scene.h"
#include "modelManager.h"

namespace scene {

    Scene::Scene()
        // Fixme: camera dimensions
        : m_camera(graphics::ViewportRect{0, 0, 1280, 720}){
        m_camera.SetPosition(glm::vec3(0, 0, 3));
    }

    void Scene::Update(float timestep) {
        for (auto& entity : m_entities) {
            entity->Update(timestep);
        }
    }

}
