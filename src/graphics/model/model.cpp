#include <pch.h>
#include "model.h"

namespace graphics {

    Model::Model() {
    }

    void Model::AddNode(std::string& name, ModelNode& node) {
        m_nameToNodeIndex.emplace(name, m_nameToNodeIndex.size());
        m_modelNodes.push_back(node);
    }

}
