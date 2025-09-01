#include <pch.h>
#include "modelManager.h"

#include "graphics/model/modelLoader.h"

namespace scene {

    std::shared_ptr<graphics::Model> ModelManager::GetModel(std::string name) {
        if (m_models.contains(name)) {
            return m_models.at(name);
        }

        std::shared_ptr<graphics::Model> model = graphics::modelLoader::LoadModel(name);
        m_models.emplace(name, model);

        return model;
    }

}
