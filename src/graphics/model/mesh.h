#ifndef MESH_H
#define MESH_H

#include "graphics/vertexArray.h"

namespace graphics {

    class Mesh {
    public:
        Mesh(const std::string &name);
        ~Mesh() = default;

        void AddSubMesh(const std::shared_ptr<VertexArray> vao);

    private:
        struct SubMesh {
            std::shared_ptr<VertexArray> vao;
            //FIXME: Add material
        };

    private:
        std::vector<SubMesh> m_submeshes;
    };

}

#endif /* MESH.H */
