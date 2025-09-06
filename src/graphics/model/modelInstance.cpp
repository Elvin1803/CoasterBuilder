#include <pch.h>
#include "modelInstance.h"

namespace graphics {

    ModelInstance::ModelInstance(std::shared_ptr<graphics::Model> model)
        : m_model(model) {
        for (auto& modelNode : model->m_modelNodes) {
            m_instanceNodes.emplace_back();
        }
    }

    void ModelInstance::RecalculateTransforms() {
        auto& modelNodes = m_model->m_modelNodes;

        for (uint32_t i = 0; i < m_instanceNodes.size(); i++) {
            // Check if parent transform is dirty
            if (modelNodes[i].parentIndex != -1) {
                if (m_instanceNodes[modelNodes[i].parentIndex].isDirty) {
                    m_instanceNodes[i].isDirty = true;
                }
            }

            if (m_instanceNodes[i].isDirty) {
                auto orientation = glm::quat(glm::radians(m_instanceNodes[i].rotation) * glm::vec3(1, -1, -1));
                m_instanceNodes[i].modelMatrix =
                    glm::translate(glm::mat4(1.0f), m_instanceNodes[i].position) *
                    glm::toMat4(orientation) *
                    glm::scale(glm::mat4(1.0f), m_instanceNodes[i].scale);

                if (modelNodes[i].parentIndex != -1) {
                    m_instanceNodes[i].modelMatrix =
                        m_instanceNodes[modelNodes[i].parentIndex].modelMatrix * m_instanceNodes[i].modelMatrix;
                }
            }
        }

        // Recalculation is done, set all dirty flags to false
        for (uint32_t i = 0; i < m_instanceNodes.size(); i++) {
            m_instanceNodes[i].isDirty = false;
        }
    }

    InstanceNode& ModelInstance::GetMeshTransform(std::string mesh) {
        return m_instanceNodes[m_model->m_nameToNodeIndex[mesh]];
    }

}
