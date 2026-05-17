#ifndef RENDERER_H
#define RENDERER_H

#include <window.h>
#include <scene/scene.h>

#include "graphicsAPI/buffers/buffer.h"
#include "graphicsAPI/buffers/vertexArray.h"
#include "3d/shaders/screenShader.h"

using namespace graphics;

class Renderer {
public:
    Renderer(Window *window);

    void BeginFrame();
    void EndFrame();

    void Resize(uint32_t width, uint32_t height);

    void Render(scene::Scene& scene);

private:
    Window* m_window;
    std::shared_ptr<FrameBuffer> m_fboScene;
    graphics::ScreenShader m_screenShader;
    graphics::VertexArray m_emptyVAO;
};


#endif /* RENDERER_H */
