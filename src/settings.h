#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "graphics/2d/frame.h"

struct Resolution {
    uint32_t width = 1280;
    uint32_t height = 720;
};

enum class DisplayMode { WINDOWED, BORDERLESS };

struct Settings
{
    // Video
    Resolution resolution;
    DisplayMode displayMode = DisplayMode::WINDOWED;
    bool vsync = false;
    std::optional<uint32_t> maxFPS{};
};

namespace UI {

    class SettingsMenu : public Frame
    {
    public:
        virtual void Render() override;
    };

}


#endif /* _SETTINGS_H_ */
