#include "graphics/buffer.h"
#include "graphics/bufferLayout.h"
#include "graphics/model/model.h"
#include "graphics/vertexArray.h"
#include "scene/scene.h"
#include "utils/logger.h"
#include "utils/paths.h"

#include "gui/window.h"

#include "scene/camera.h"
#include "graphics/shaders/simpleShader.h"

#include "graphics/model/modelLoader.h"

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif

    LOG_TRACE("Starting CoasterBuilder");
    UI::Window window(1280, 720, "CoasterBuilder");

    scene::Scene scene;

    // ====== FIXME: Clean this =======
#ifdef DEBUG
    graphics::SimpleShader shader;

    const float vertices[] = { -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
                               0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
                               0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f
    };
    const uint32_t indices[] = { 0, 1, 2 };
    std::shared_ptr<graphics::BufferLayout> layout = std::make_shared<graphics::BufferLayout>(
        std::vector<graphics::BufferLayoutElement>{
            { 3, graphics::ShaderDataType::Float }, // position
            { 3, graphics::ShaderDataType::Float }, // color
        });

    std::unique_ptr<graphics::VertexBuffer> vbo =
        std::make_unique<graphics::VertexBuffer>(vertices, sizeof(vertices), layout);
    std::unique_ptr<graphics::IndexBuffer> ibo =
        std::make_unique<graphics::IndexBuffer>(indices, sizeof(indices));

    graphics::VertexArray vao(std::move(vbo), std::move(ibo));
#endif /* DEBUG */
    //=================================

    while (!window.ShouldClose()) {
        window.PollEvents();

        scene.Render();
#ifdef DEBUG
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
#endif /* DEBUG */

        window.SwapBuffers();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
