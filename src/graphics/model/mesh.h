#ifndef MESH_H
#define MESH_H

#include "graphics/buffers/vertexArray.h"

namespace graphics {

    class Mesh {
    private:
        struct SubMesh {
            std::shared_ptr<VertexArray> vao;
            //FIXME: Add material
        };

    public:
        Mesh() = default;
        ~Mesh() = default;

        void AddSubMesh(const std::shared_ptr<VertexArray> vao);
        std::vector<SubMesh> GetSubMesh() { return m_submeshes; };

    private:
        std::vector<SubMesh> m_submeshes;
    };

}

#endif /* MESH.H */
