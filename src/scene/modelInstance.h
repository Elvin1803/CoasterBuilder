#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include "graphics/model/model.h"

namespace scene {

    struct Transform {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
    };

    class ModelInstance {
    public:
        ModelInstance(std::shared_ptr<graphics::Model> model);
        ~ModelInstance() = default;

        void SetTransform(std::string mesh, Transform tranform);

    private:
        std::shared_ptr<graphics::Model> m_model;
        std::unordered_map<std::string, Transform> m_transforms;
    };

}

#endif /* MODEL_INSTANCE.H */
