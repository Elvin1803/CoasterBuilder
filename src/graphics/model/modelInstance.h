#ifndef MODEL_INSTANCE_H
#define MODEL_INSTANCE_H

#include "graphics/model/model.h"

class Renderer;

namespace graphics {

    struct InstanceNode {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        bool isDirty = true;
    };

    class ModelInstance {
        friend class ::Renderer;

    public:
        ModelInstance(std::shared_ptr<graphics::Model> model);

        glm::vec3 GetMeshPosition(std::string mesh) { return GetMeshTransform(mesh).position; };
        glm::vec3 GetMeshRotation(std::string mesh) { return GetMeshTransform(mesh).rotation; };
        glm::vec3 GetMeshScale(std::string mesh) { return GetMeshTransform(mesh).scale; };

        void SetMeshPosition(std::string mesh, glm::vec3 position) {
            GetMeshTransform(mesh).position = position;
            GetMeshTransform(mesh).isDirty = true;
        };
        void SetMeshRotation(std::string mesh, glm::vec3 rotation) {
            GetMeshTransform(mesh).rotation = rotation;
            GetMeshTransform(mesh).isDirty = true;
        };
        void SetMeshScale(std::string mesh, glm::vec3 scale) {
            GetMeshTransform(mesh).scale = scale;
            GetMeshTransform(mesh).isDirty = true;
        };

    private:
        void RecalculateTransforms();
        InstanceNode& GetMeshTransform(std::string mesh);

    private:
        std::shared_ptr<graphics::Model> m_model;
        std::vector<InstanceNode> m_instanceNodes;
    };

}

#endif /* MODEL_INSTANCE.H */
