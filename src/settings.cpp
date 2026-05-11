#include "settings.h"
#include "imgui.h"
#include "utils/logger.h"

#include "app.h"

namespace UI{

    const struct DisplayModeOption { const char* label; DisplayMode mode; } displayModeOptions[] = {
        { "WINDOW",   DisplayMode::WINDOWED },
        { "BORDERLESS WINDOW", DisplayMode::BORDERLESS },
    };

    const struct ResolutionOption {  const char* label; uint32_t width; uint32_t height; } resolutionOptions[] = {
        { "1920x1080", 1920, 1080 },
        { "1760x900" , 1760, 990  },
        { "1680x1050", 1680, 1050 },
        { "1600x900" , 1600, 900  },
        { "1440x900" , 1440, 900  },
        { "1366x768" , 1366, 768  },
        { "1280x800" , 1280, 800  },
        { "1280x720" , 1280, 720  },
    };

    const struct FPSOption { const char* label; uint32_t value; } FPSOptions[] = {
        { "24 FPS",    24  },
        { "30 FPS",    30  },
        { "60 FPS",    60  },
        { "120 FPS",   120 },
        { "144 FPS",   144 },
        { "240 FPS",   240 },
        { "Unlimited", 0   },
    };

    void SettingsMenu::Render() {
        auto& settings = app::Application::GetApplication().GetSettings();

        ImGui::Begin("Settings menu");
        ImGui::Text("Video Settings");

        ImGui::Separator();

        // Display Mode
        int currentDisplayIdx = 0;
        for (int n = 0; n < IM_COUNTOF(displayModeOptions); n++) {
            if (displayModeOptions[n].mode == settings.displayMode) {
                currentDisplayIdx = n;
                break;
            }
        }
        if (ImGui::Combo("Display Mode", &currentDisplayIdx,
            [](void* data, int idx, const char** out_text) {
                *out_text = ((DisplayModeOption*)data)[idx].label;
                return true;
            }, (void*)displayModeOptions, IM_COUNTOF(displayModeOptions)))
        {
            settings.displayMode = displayModeOptions[currentDisplayIdx].mode;
        }
        // Resolution
        int currentResolutionIdx = 0;
        for (int n = 0; n < IM_COUNTOF(resolutionOptions); n++) {
            if (resolutionOptions[n].width == settings.resolution.width
             && resolutionOptions[n].height == settings.resolution.height) {
                currentResolutionIdx = n;
                break;
            }
        }
        if (ImGui::Combo("Resolution", &currentResolutionIdx,
            [](void* data, int idx, const char** out_text) {
                *out_text = ((ResolutionOption*)data)[idx].label;
                return true;
            }, (void*)resolutionOptions, IM_COUNTOF(resolutionOptions)))
        {
            settings.resolution.width  = resolutionOptions[currentResolutionIdx].width;
            settings.resolution.height = resolutionOptions[currentResolutionIdx].height;
        }

        // VSync
        ImGui::Checkbox("Enable VSync", &settings.vsync);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        if (ImGui::Button("Apply Changes", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
            app::Application::GetApplication().ApplyVideoSettings();
        }
        ImGui::PopStyleColor();

        ImGui::Separator();

        // Limit FPS
        int currentIndex = IM_COUNTOF(FPSOptions) - 1;
        if (settings.maxFPS.has_value()) {
            for (int i = 1; i < IM_COUNTOF(FPSOptions); i++) {
                if (FPSOptions[i].value == settings.maxFPS.value()) {
                    currentIndex = i;
                    break;
                }
            }
        }
        if (ImGui::Combo("Frame Rate Limit", &currentIndex,
            [](void* data, int idx, const char** out_text) {
                *out_text = ((FPSOption*)data)[idx].label;
                return true;
            }, (void*)FPSOptions, IM_COUNTOF(FPSOptions)))
        {
            if (FPSOptions[currentIndex].value == 0) {
                settings.maxFPS = std::nullopt;
            } else {
                settings.maxFPS = FPSOptions[currentIndex].value;
            }
        }

        ImGui::End();
    }
}
