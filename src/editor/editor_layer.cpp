#include "enpch.h"
#include "editor_layer.h"
#include "engine.h"
#include <imgui.h>

namespace engine {
    EditorLayer::EditorLayer()
        : Layer("editor_layer") {

    }

    void EditorLayer::on_imgui_render() {
        {
            Window& window = Engine::get_instance()->get_window();
            int width = window.get_width();
            int height = window.get_height();
            bool fullscreen = window.get_fullscreen();
            bool vsync = window.get_vsync();

            ImGui::Begin("Configs");
            ImGui::SliderInt("Width", &width, 640, 1366);
            ImGui::SliderInt("Heght", &height, 300, 768);
            ImGui::Checkbox("Fullscreen", &fullscreen);
            ImGui::Checkbox("V-Sync", &vsync);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();

            if (width != window.get_width()) {
                window.set_width(width);
            }
            if (height != window.get_height()) {
                window.set_height(height);
            }
            if (fullscreen != window.get_fullscreen()) {
                window.set_fullscreen(fullscreen);
            }
            if (vsync != window.get_vsync()) {
                window.set_vsync(vsync);
            }
        }
    }
}
