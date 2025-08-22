#include <pch.h>
#include "scene.h"

#include "graphics/model/modelLoader.h"

namespace scene {

    Scene::Scene()
        : m_camera(Camera({ .x = 0, .y = 0, .width = 1280, .height = 720 })){
        //std::shared_ptr<graphics::Model> model = graphics::modelLoader::LoadModel("test.cbdat");
    }

    void Scene::Update(float timestep) {
    }

    void Scene::Render() {
        glViewport(0, 0, 1280, 720);
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        auto temp = m_camera.GetPosition();
        temp.z += 0.0001f;
        m_camera.SetPosition(temp);
        m_shader.UseShader();
        auto& mvp = m_camera.GetViewProjection();
        m_shader.setMVP(mvp);

        /*
        // TODO: model multiplication
        for (auto& model : m_models) {
            auto& mvp = m_camera.GetViewProjection();
            m_shader.setMVP(mvp);
            //model.Render(); // FIXME mais la j'ai la flemme wola
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        }
        */

    }

}
