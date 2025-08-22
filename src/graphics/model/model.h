#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

namespace graphics {

    struct Node {
        std::string name;
        glm::vec3 origin = glm::vec3(0); // Local origin
        glm::mat4 defaultTransform = glm::mat4(1.0f);
        std::shared_ptr<Mesh> mesh = nullptr;
        std::vector<Node> children;
    };

    class Model {
    public:
        Model(const std::string &fileName);
        ~Model() = default;

    private:
        Node m_rootNode;
    };

}

#endif /* MODEL.H */
