#include <pch.h>
#include "mesh.h"

namespace graphics {

    void Mesh::AddSubMesh(std::shared_ptr<VertexArray> vao) {
        SubMesh submesh;
        submesh.vao = vao;
        submesh.material = std::make_shared<Material>();
        m_submeshes.push_back(submesh);
    }

    void Mesh::AddSubMesh(std::shared_ptr<VertexArray> vao, std::shared_ptr<Material> material) {
        SubMesh submesh;
        submesh.vao = vao;
        submesh.material = material;
        m_submeshes.push_back(submesh);
    }

}
