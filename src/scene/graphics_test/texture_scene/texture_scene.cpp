#ifdef DEBUG

#include <pch.h>
#include "texture_scene.h"
#include "graphics/3d/modelInstance.h"
#include "texture_plane.h"

namespace scene {

    TextureScene::TextureScene() {
        auto model = m_modelManager.GetModel("texture_test.cbmodel");
        graphics::ModelInstance modelInstance(model);
        m_entities.emplace_back(std::make_unique<TexturePlane>(modelInstance));
    }

}


#endif //DEBUG
