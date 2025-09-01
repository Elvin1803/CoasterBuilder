#include <pch.h>
#include "renderer.h"

#include "graphics/shaders/simpleShader.h"

Renderer::Renderer(Window *window)
    : m_window(window) {}

void Renderer::BeginFrame() {
    glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::EndFrame() {
}

void Renderer::Render(std::vector<graphics::ModelInstance> models, graphics::Camera cam) {
    graphics::SimpleShader shader;
    shader.UseShader();

    auto& viewProj = cam.GetViewProjection();

    // FIXME: Pas opti
    for (auto& modelInstance : models) {
        const auto& modelNodes =  modelInstance.GetModel()->GetNodes();
        const auto& instanceNodes =  modelInstance.GetNodes();

        for (auto i = 0; i < modelNodes.size(); i++) {
            const auto& modelNode = modelNodes[i];
            const auto& instanceNode = instanceNodes[i];

            // FIXME: Calculate modelMatrix here
            auto mvp = viewProj;
            shader.setMVP(mvp);

            for (auto& submesh : modelNode.mesh->GetSubMesh()) {
                submesh.vao->Bind();
                glDrawElements(GL_TRIANGLES, submesh.vao->GetIndexLength(), GL_UNSIGNED_INT, 0);
            }
        }
    }

}
