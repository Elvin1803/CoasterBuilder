#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include <scene/scene.h>

#include <graphics/3d/shaders/compute/skyViewLUT.h>

namespace UI {

    class UI_manager
    {
    public:
        UI_manager(GLFWwindow *window);
        ~UI_manager();

        void Render(scene::Scene& scene);

#ifdef DEBUG
    private:
        graphics::TransmittanceLUT m_TlutDebug;
        graphics::MultiScatLUT m_MSlutDebug;
        graphics::SkyViewLUT m_SVlutDebug;
#endif
    };


}

#endif /* _UI_MANAGER_H_ */
