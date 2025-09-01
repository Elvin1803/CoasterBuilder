#include <pch.h>
#include "modelInstance.h"

namespace graphics {

    ModelInstance::ModelInstance(std::shared_ptr<graphics::Model> model)
        : m_model(model) {
        // FIXME
        for (auto& modelNode : model->m_modelNodes) {
            m_instanceNodes.emplace_back();
        }
    }

}
