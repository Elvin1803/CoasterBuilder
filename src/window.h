#ifndef WINDOW_H
#define WINDOW_H

class Window {
public:
    Window(const uint16_t width, const uint16_t height, const std::string &title);
    ~Window();

    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    void PollEvents() const;
    bool ShouldClose() const;
    void SwapBuffers() const;

public:
    const uint16_t GetWidth() const { return m_width; }
    const uint16_t GetHeight() const { return m_height; }

private:
    uint16_t m_width, m_height;

private:
    GLFWwindow *m_window;
};

#endif /* WINDOW_H */
