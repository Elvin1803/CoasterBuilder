#include <pch.h>
#include "mesh.h"

namespace graphics {

    void Mesh::AddSubMesh(const std::shared_ptr<VertexArray> vao) {
        SubMesh submesh;
        submesh.vao = vao;
        m_submeshes.push_back(submesh);
    }

}
