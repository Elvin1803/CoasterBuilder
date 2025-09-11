#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

namespace graphics {

    struct ModelNode {
        glm::vec3 origin = glm::vec3(0); // Local origin
        std::shared_ptr<Mesh> mesh = nullptr;
        int32_t parentIndex = -1;
    };

    class Model {
        friend class ModelInstance;

    public:
        Model();
        ~Model() = default;

        void AddNode(std::string& name, std::string& parentName, ModelNode& node);
        std::vector<ModelNode> GetNodes() { return m_modelNodes; };

    private:
        std::vector<ModelNode> m_modelNodes;
        std::unordered_map<std::string, uint16_t> m_nameToNodeIndex;
    };

}

#endif /* MODEL.H */
