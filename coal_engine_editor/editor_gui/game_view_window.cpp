#include <coal_engine.h>
#include "game_view_window.h"
#include <imgui.h>

namespace engine::editor {
    void GameViewWindow::render() {
        const ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Game Viewport", nullptr, window_flags);

        Texture& texture = Engine::get_instance()->get_framebuffer().get_texture();

        ImVec2 window_size = ImGui::GetContentRegionAvail();
        window_size.x -= ImGui::GetScrollX();
        window_size.y -= ImGui::GetScrollY();

        float aspect_ratio = (float)texture.get_width() / (float)texture.get_height();

        ImVec2 window_aspect_size;
        window_aspect_size.x = window_size.x;
        window_aspect_size.y = window_aspect_size.x / aspect_ratio;
        if (window_aspect_size.y > window_size.y) {
            window_aspect_size.y = window_size.y;
            window_aspect_size.x = window_aspect_size.y * aspect_ratio;
        }

        ImVec2 window_position = ImVec2((window_size.x * 0.5f) - (window_aspect_size.x * 0.5f) + ImGui::GetCursorPosX(), (window_size.y * 0.5f) - (window_aspect_size.y * 0.5f) + ImGui::GetCursorPosY());

        ImGui::SetCursorPos(window_position);
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture.get_id())), window_aspect_size, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

        ImGui::End();
        ImGui::PopStyleVar();
    }
}
