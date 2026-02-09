#ifndef _APP_H_
#define _APP_H_

namespace app {

    class app_state
    {
    public:
        static app_state& GetAppState();

        void SetFPS(float fps);
        float GetFPS();

    private:
        static app_state* m_instance;

        float m_fps = 0.f;

    private:
        app_state() = default;
        ~app_state() = default;
    };

}

#endif /* _APP_H_ */
