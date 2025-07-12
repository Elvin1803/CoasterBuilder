#ifndef WINDOW_H
#define WINDOW_H

namespace UI {

    class Window {
    public:
        Window(const uint16_t width, const uint16_t height, const std::string &title);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(Window&) = delete;

        void PollEvents() const;
        bool ShouldClose() const;
        void SwapBuffers() const;

    private:
        GLFWwindow *m_window;
    };

} // UI

#endif /* WINDOW_H */
