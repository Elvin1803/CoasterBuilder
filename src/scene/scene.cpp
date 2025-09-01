#include <pch.h>
#include "scene.h"

namespace scene {

    Scene::Scene()
        // Fixme: camera dimensions
        : m_camera(graphics::ViewportRect{0, 0, 1280, 720}){
    }

    void Scene::Update(float timestep) {
        auto temp = m_camera.GetPosition();
        temp.z += 0.0001f;
        m_camera.SetPosition(temp);
    }

    void Scene::SpawnModel(std::string name) {
        auto model = m_modelManager.GetModel(name);

        m_models.emplace_back(model);
    }

}
