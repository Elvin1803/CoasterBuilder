#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "modelInstance.h"
#include "graphics/shaders/simpleShader.h"

namespace scene {

    class Scene {
    public:
        Scene();
        ~Scene() = default;

        void Update(float timestep);
        void Render();

    private:
        Camera m_camera;
        graphics::SimpleShader m_shader;
        std::vector<ModelInstance> m_models;
    };

}

#endif /* SCENE.H */
