#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include <scene/scene.h>

namespace UI {

    class UI_manager
    {
    public:
        UI_manager(GLFWwindow *window);
        ~UI_manager();

        void Render(scene::Scene& scene);
    };


}

#endif /* _UI_MANAGER_H_ */
