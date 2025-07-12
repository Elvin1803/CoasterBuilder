#include "renderer/buffer.h"
#include "renderer/bufferLayout.h"
#include "renderer/vertexArray.h"
#include "utils/logger.h"
#include "utils/paths.h"

#include "gui/window.h"

#include "renderer/shaders/simpleShader.h"

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif

    LOG_TRACE("Starting CoasterBuilder");
    UI::Window window(1280, 720, "CoasterBuilder");

    // ====== FIXME: Clean this =======
    renderer::SimpleShader shader;

    const float vertices[] = { -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
                               0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
                               0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f
    };
    const uint32_t indices[] = { 0, 1, 2 };
    std::shared_ptr<renderer::BufferLayout> layout = std::make_shared<renderer::BufferLayout>(
        std::vector<renderer::BufferLayoutElement>{
            { 3, renderer::ShaderDataType::Float }, // position
            { 3, renderer::ShaderDataType::Float }, // color
        });

    std::unique_ptr<renderer::VertexBuffer> vbo =
        std::make_unique<renderer::VertexBuffer>(vertices, sizeof(vertices), layout);
    std::unique_ptr<renderer::IndexBuffer> ibo =
        std::make_unique<renderer::IndexBuffer>(indices, sizeof(indices));

    renderer::VertexArray vao(std::move(vbo), std::move(ibo));
    //=================================

    while (!window.ShouldClose()) {
        window.PollEvents();

        // ====== FIXME: Clean this =======
        glViewport(0, 0, 1280, 720);
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        shader.UseShader();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //=================================

        window.SwapBuffers();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
