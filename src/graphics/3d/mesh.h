#ifndef MESH_H
#define MESH_H

#include "graphics/graphicsAPI/buffers/vertexArray.h"
#include "graphics/graphicsAPI/shaders/material.h"

namespace graphics {

    class Mesh {
    private:
        struct SubMesh {
            std::shared_ptr<VertexArray> vao;
            std::shared_ptr<Material> material;
        };

    public:
        void AddSubMesh(std::shared_ptr<VertexArray> vao);
        void AddSubMesh(std::shared_ptr<VertexArray> vao, std::shared_ptr<Material> material);
        std::vector<SubMesh> GetSubMesh() { return m_submeshes; };

    private:
        std::vector<SubMesh> m_submeshes;
    };

}

#endif /* MESH.H */
