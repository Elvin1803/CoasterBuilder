#ifndef FRAME_H
#define FRAME_H

namespace UI {

    class Frame {
    public:
        Frame();
        ~Frame();

        Frame(const Frame&) = delete;
        Frame& operator=(Frame&) = delete;

    private:
        GLFWwindow *m_window;
    };

}

#endif /* FRAME_H */
