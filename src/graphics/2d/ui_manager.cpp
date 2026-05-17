#include <pch.h>
#include "ui_manager.h"
#include "app.h"

namespace UI {

    UI_manager::UI_manager(GLFWwindow *window) {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }

    UI_manager::~UI_manager() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UI_manager::Render(scene::Scene& scene) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

#ifdef DEBUG
        ImGui::Begin("app state");
        ImGui::Text("FPS: %.3f", app::Application::GetApplication().GetFPS());
        ImGui::End();

        ImGui::Begin("Atmosphere Debug");
        // Transmittance
        uint32_t TtexId = m_TlutDebug.GetTransmittanceLUTId();
        ImTextureID imguiTTexId = (ImTextureID)(intptr_t)TtexId;
        ImGui::Image(imguiTTexId, ImVec2(512, 128), ImVec2(0, 1), ImVec2(1, 0));

        // Multi scattering
        uint32_t mstexId = m_MSlutDebug.GetMultiScatLUTId();
        ImTextureID imguimsTexId = (ImTextureID)(intptr_t)mstexId;
        ImGui::Image(imguimsTexId, ImVec2(320, 320), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
#endif

        for (auto& frame : scene.GetFrames()) {
            frame->Render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
