#include <pch.h>
#include "texture_scene.h"
#include "graphics/model/modelInstance.h"
#include "texture_plane.h"

namespace scene {

    TextureScene::TextureScene() {
        m_camera.SetPosition(glm::vec3(0,0,3));
        auto model = m_modelManager.GetModel("texture_test.cbdat");
        graphics::ModelInstance modelInstance(model);
        m_entities.emplace_back(std::make_unique<TexturePlane>(modelInstance));
    }

}
