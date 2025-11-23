#include <pch.h>
#include "model.h"

namespace graphics {

    Model::Model() {
    }

    void Model::AddNode(std::string& name, std::string& parentName, ModelNode& node) {
        m_nameToNodeIndex.emplace(name, m_nameToNodeIndex.size());

        if (parentName.size() != 0) {
            node.parentIndex = m_nameToNodeIndex[parentName];
        }

        m_modelNodes.push_back(node);
    }

}
