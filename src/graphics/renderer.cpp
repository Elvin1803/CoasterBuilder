#include <pch.h>
#include "renderer.h"

#include "glad/glad.h"
#include "graphics/3d/shaders/simpleShader.h"

Renderer::Renderer(Window *window)
    : m_window(window) {
    m_fboScene = std::make_shared<FrameBuffer>(window->GetWidth(), window->GetHeight());
    m_fboScene->AddBuffer(TextureSpecification{window->GetWidth(), window->GetHeight(),
                                               TextureFormat::RGBA8, TextureFilter::Linear});
    m_fboScene->AddBuffer(TextureSpecification{window->GetWidth(), window->GetHeight(),
                                               TextureFormat::Depth24Stencil8, TextureFilter::Nearest});

    m_fboPostProcess = std::make_shared<FrameBuffer>(window->GetWidth(), window->GetHeight());
    m_fboPostProcess->AddBuffer(TextureSpecification{window->GetWidth(), window->GetHeight(),
                                               TextureFormat::RGBA8, TextureFilter::Linear});
    m_fboPostProcess->AddBuffer(TextureSpecification{window->GetWidth(), window->GetHeight(),
                                               TextureFormat::Depth24Stencil8, TextureFilter::Nearest});
}

void Renderer::BeginFrame() {
    m_fboScene->Bind();

    glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::EndFrame() {
    // Draw result to the main framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_screenShader.UseShader();

    glActiveTexture(GL_TEXTURE0);
    // This needs to be set to the last framebuffer usedx
    glBindTexture(GL_TEXTURE_2D, m_fboPostProcess->GetColorBufferId(0));
    m_emptyVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Resize(uint32_t width, uint32_t height) {
    m_fboScene->Resize(width, height);
    m_fboPostProcess->Resize(width, height);
}

void Renderer::Render(scene::Scene& scene, float timestep) {
    // FIXME: Shaders should be in materials
    graphics::SimpleShader shader;

    auto& cam = scene.GetCamera();
    auto& viewProj = cam.GetViewProjection();

    // FIXME: Pas opti
    shader.UseShader();
    for (auto& entity : scene.GetEntities()) {
        auto modelInstance = entity->GetModel();
        modelInstance.RecalculateTransforms();
        const auto& modelNodes =  modelInstance.m_model->GetNodes();
        const auto& instanceNodes =  modelInstance.m_instanceNodes;

        for (size_t i = 0; i < modelNodes.size(); i++) {
            const auto& modelNode = modelNodes[i];
            const auto& instanceNode = instanceNodes[i];

            auto mvp = viewProj * instanceNode.modelMatrix;
            shader.setMVP(mvp);

            for (auto& submesh : modelNode.mesh->GetSubMesh()) {
                shader.setMaterial(submesh.material.get());
                submesh.vao->Bind();
                glDrawElements(GL_TRIANGLES, submesh.vao->GetIndexLength(), GL_UNSIGNED_INT, 0);
            }
        }
    }

    // Render tracks
    for (auto& track : scene.GetTracks()) {
        track.Render(viewProj);
    }

    // Render atmosphere
    glm::mat4 invViewProj = glm::inverse(viewProj);
    float height = cam.GetPosition().y + 6.3602f;

    // Draw result to post process fbo
    m_fboPostProcess->Bind();
    glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);

    m_atmosphereShader.Update(timestep);
    m_atmosphereShader.Render(height, invViewProj);
    m_emptyVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
