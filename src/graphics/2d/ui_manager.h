#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

namespace UI {

    class UI_manager
    {
    public:
        UI_manager(GLFWwindow *window);
        ~UI_manager();

        void Render();
    };


}

#endif /* _UI_MANAGER_H_ */
