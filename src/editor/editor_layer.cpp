#include "enpch.h"
#include "editor_layer.h"
#include "engine.h"
#include <imgui.h>
#include "core/rendering/rendering_api.h"
#include "core/rendering/renderer.h"
#include "core/logging/log_window.h"
#include "utility/string_utility.h"

// TODO: Scene view

namespace engine::editor {
    EditorLayer::EditorLayer()
        : Layer("editor_layer") {
        _game_view_window = create_scope<GameViewWindow>();
    }

    void EditorLayer::on_imgui_render() {
        const ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        Window& window = Engine::get_instance()->get_window();

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float min_win_size_x = style.WindowMinSize.x;
        style.WindowMinSize.x = window.get_width() * 0.175f; // 17.5% of the screen
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        style.WindowMinSize.x = min_win_size_x;

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New", "Ctrl+N"))
                    EN_LOG_INFO("New scene");

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    EN_LOG_INFO("Open file");

                if (ImGui::MenuItem("Save", "Ctrl+S"))
                    EN_LOG_INFO("Save scene");

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    EN_LOG_INFO("Save scene as");

                if (ImGui::MenuItem("Exit"))
                    EN_LOG_INFO("Exit");

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Begin("Metrics");
        auto metrics = Engine::get_instance()->get_metrics();
        auto rendering_statistics = Renderer::get_stats();
        ImGui::Text(engine::format("FPS: {}", metrics.fps_as_double).c_str());
        ImGui::Text(engine::format("ms: {}", metrics.ms_as_double).c_str());
        ImGui::Text(engine::format("Frame count: {}", metrics.total_frame_count).c_str());
        ImGui::Text(engine::format("Quad Count: {}", rendering_statistics.quad_count).c_str());
        ImGui::Text(engine::format("Draw Calls: {}", rendering_statistics.draw_calls).c_str());
        ImGui::End();

        int width = window.get_width();
        int height = window.get_height();
        bool fullscreen = window.get_fullscreen();
        bool vsync = window.get_vsync();

        ImGui::Begin("Settings");
        ImGui::SliderInt("Width", &width, 640, 1366);
        ImGui::SliderInt("Heght", &height, 300, 768);
        ImGui::Checkbox("Fullscreen", &fullscreen);
        ImGui::Checkbox("V-Sync", &vsync);
        ImGui::End();

        if (width != window.get_width())
            window.set_width(width);
        if (height != window.get_height())
            window.set_height(height);
        if (fullscreen != window.get_fullscreen())
            window.set_fullscreen(fullscreen);
        if (vsync != window.get_vsync())
            window.set_vsync(vsync);

        Logger::get_log_window()->render();
        _game_view_window->render();

        ImGui::End();
    }
}
