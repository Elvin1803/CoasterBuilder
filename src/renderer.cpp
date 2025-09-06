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

void Renderer::Render(scene::Scene& scene) {
    // FIXME: Shaders should be in materials
    graphics::SimpleShader shader;
    shader.UseShader();

    auto& cam = scene.GetCamera();
    auto& viewProj = cam.GetViewProjection();

    // FIXME: Pas opti
    for (auto& entity : scene.GetEntities()) {
        auto modelInstance = entity->GetModel();
        modelInstance.RecalculateTransforms();
        const auto& modelNodes =  modelInstance.m_model->GetNodes();
        const auto& instanceNodes =  modelInstance.m_instanceNodes;

        for (auto i = 0; i < modelNodes.size(); i++) {
            const auto& modelNode = modelNodes[i];
            const auto& instanceNode = instanceNodes[i];

            // FIXME: Calculate modelMatrix here
            auto mvp = viewProj * instanceNodes[i].modelMatrix;
            shader.setMVP(mvp);

            for (auto& submesh : modelNode.mesh->GetSubMesh()) {
                submesh.vao->Bind();
                glDrawElements(GL_TRIANGLES, submesh.vao->GetIndexLength(), GL_UNSIGNED_INT, 0);
            }
        }
    }

}
