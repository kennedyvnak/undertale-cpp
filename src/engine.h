#pragma once

#include <string>
#include "core/base.h"
#include "core/rendering/layers/layer_stack.h"
#include "imgui/imgui_layer.h"
#include "editor/editor_layer.h"
#include "core/rendering/window.h"
#include "core/rendering/framebuffer.h"

namespace engine {
    class Layer;

    struct EngineCommandLineArgs {
        int count = 0;
        char** args = nullptr;

        const char* operator[](int index) const {
            EN_ASSERT(index < count, "Index out of range.");
            return args[index];
        }
    };

    struct EngineSpecification {
        std::string name;
        EngineCommandLineArgs command_line_args;
    };

    struct EngineMetrics {
        static const double frame_check_interval;
        float fps = 0.0f;
        float ms = 0.0f;
        double fps_as_double = 0.0;
        double ms_as_double = 0.0;
        unsigned long long int total_frame_count = 0;
    };

    class Engine {
    public:
        Engine(const EngineSpecification& specification);
        ~Engine() = default;

        void run();

        static Engine* create_engine(EngineCommandLineArgs args);

        void push_layer(Layer* layer);
        void push_overlay(Layer* layer);

        inline static Engine* get_instance() { return _instance; }
        inline const EngineSpecification& get_specifications() const& { return _specs; }
        inline EngineMetrics get_metrics() const { return _metrics; }
        inline Window& get_window() const { return *_window; }
        inline Framebuffer& get_framebuffer() const { return *_framebuffer; }
    private:
        static Engine* _instance;
        Scope<Window> _window;
        EngineSpecification _specs;
        EngineMetrics _metrics;
        Scope<Framebuffer> _framebuffer;
        LayerStack _layer_stack;
        imgui::ImGuiLayer* _imgui_layer;
        editor::EditorLayer* _editor_layer;

        float _fps_previous_time;
        float _frame_count;

        void calculate_fps();
    };
}
