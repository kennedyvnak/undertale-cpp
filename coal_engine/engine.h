#pragma once

#include <string>
#include <vector>
#include "core/base.h"
#include "core/rendering/layers/layer_stack.h"
#include "core/rendering/window.h"
#include "core/rendering/viewport.h"
#include "core/rendering/framebuffer.h"
#include "core/rendering/camera.h"
#include "entities/rendering/texture_renderer.h"
#ifndef DISABLE_IMGUI
#include "imgui/imgui_layer.h"
#endif

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
        ~Engine();

        void run();

        void push_layer(Layer* layer);
        void push_overlay(Layer* layer);

        inline static Engine* get_instance() { return _instance; }
        inline const EngineSpecification& get_specifications() const& { return _specs; }
        inline EngineMetrics get_metrics() const { return _metrics; }
        inline Window& get_window() const { return *_window; }
        inline Viewport& get_viewport() const { return *_viewport; }
        inline Framebuffer& get_framebuffer() const { return _viewport->get_framebuffer(); }
        inline Ref<Camera> get_camera() const { return _camera; }
    private:
        static Engine* _instance;
        Scope<Window> _window;
        EngineSpecification _specs;
        EngineMetrics _metrics;
        Scope<Viewport> _viewport;
        Ref<Camera> _camera;
        LayerStack _layer_stack;
#ifndef DISABLE_IMGUI
        imgui::ImGuiLayer* _imgui_layer;
#endif // DISABLE_IMGUI
        std::vector<Scope<entities::TextureRenderer>> _texture_renderers;

        float _fps_previous_time;
        float _frame_count;

        void calculate_fps();
    };

    extern Engine* create_engine(EngineCommandLineArgs args);
}
