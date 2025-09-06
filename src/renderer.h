#ifndef RENDERER_H
#define RENDERER_H

#include "window.h"
#include "scene/scene.h"

class Renderer {
public:
    Renderer(Window *window);
    ~Renderer() = default;

    void BeginFrame();
    void EndFrame();

    void Render(scene::Scene& scene);

private:
    Window* m_window;
};


#endif /* RENDERER_H */
