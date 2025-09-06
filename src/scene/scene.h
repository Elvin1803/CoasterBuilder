#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "modelManager.h"

#include "graphics/camera.h"

namespace scene {

    class Scene {
    public:
        Scene();
        ~Scene() = default;

        void Update(float timestep);
        void Render();

        graphics::Camera& GetCamera() { return m_camera; };
        std::vector<std::unique_ptr<Entity>>& GetEntities() { return m_entities; };

    protected:
        graphics::Camera m_camera;
        std::vector<std::unique_ptr<Entity>> m_entities;

    protected:
        ModelManager m_modelManager;
    };

}

#endif /* SCENE.H */
