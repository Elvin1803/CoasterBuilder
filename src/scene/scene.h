#ifndef SCENE_H
#define SCENE_H

#include "modelManager.h"

#include "graphics/model/modelInstance.h"
#include "graphics/camera.h"

namespace scene {

    class Scene {
    public:
        Scene();
        ~Scene() = default;

        void Update(float timestep);
        void Render();

        graphics::Camera& GetCamera() { return m_camera; };
        std::vector<graphics::ModelInstance>& GetModels() { return m_models; };

        void SpawnModel(std::string name);

    private:
        graphics::Camera m_camera;
        std::vector<graphics::ModelInstance> m_models;

    private:
        ModelManager m_modelManager;
    };

}

#endif /* SCENE.H */
