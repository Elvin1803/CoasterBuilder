#ifndef MESH_H
#define MESH_H

#include "graphics/buffers/vertexArray.h"
#include "material.h"

namespace graphics {

    class Mesh {
    private:
        struct SubMesh {
            std::shared_ptr<VertexArray> vao;
            std::shared_ptr<Material> material;
        };

    public:
        Mesh() = default;
        ~Mesh() = default;

        void AddSubMesh(std::shared_ptr<VertexArray> vao);
        void AddSubMesh(std::shared_ptr<VertexArray> vao, std::shared_ptr<Material> material);
        std::vector<SubMesh> GetSubMesh() { return m_submeshes; };

    private:
        std::vector<SubMesh> m_submeshes;
    };

}

#endif /* MESH.H */
