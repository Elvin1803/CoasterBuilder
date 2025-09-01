#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include "graphics/model/model.h"

namespace graphics {

    struct InstanceNode {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
    };

    class ModelInstance {
    public:
        ModelInstance(std::shared_ptr<graphics::Model> model);
        ~ModelInstance() = default;

        std::shared_ptr<graphics::Model> GetModel() { return m_model; }
        std::vector<InstanceNode> GetNodes() { return m_instanceNodes; }

    private:
        std::shared_ptr<graphics::Model> m_model;
        std::vector<InstanceNode> m_instanceNodes;
    };

}

#endif /* MODEL_INSTANCE.H */
