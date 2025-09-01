#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"

#include "graphics/camera.h"
#include "graphics/model/modelInstance.h"

class Renderer {
public:
    Renderer(Window *window);
    ~Renderer() = default;

    void BeginFrame();
    void EndFrame();

    void Render(std::vector<graphics::ModelInstance> models, graphics::Camera cam);

private:
    Window* m_window;
};


#endif /* RENDERER_H */
