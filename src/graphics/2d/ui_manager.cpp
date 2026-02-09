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

    void UI_manager::Render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("app state");
        ImGui::Text("FPS: %.3f", app::app_state::GetAppState().GetFPS());
        ImGui::End();

        ImGui::Begin("harcelement");
        ImGui::End();
    }

}
