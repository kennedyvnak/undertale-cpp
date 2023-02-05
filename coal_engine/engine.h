#pragma once

#include <string>
#include <vector>
#include "core/base.h"
#include "core/os/time.h"
#include "core/events/engine_event.h"
#include "core/events/window_event.h"
#include "core/events/key_event.h"
#include "core/rendering/layers/layer_stack.h"
#include "core/rendering/window.h"
#include "core/rendering/viewport.h"
#include "core/rendering/framebuffer.h"
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
        static const TimeValue frame_check_interval;
        TimeValue fps = 0.0_t;
        TimeValue ms = 0.0_t;
        unsigned long long int total_frame_count = 0;
    };

    class Engine {
    public:
        Engine(const EngineSpecification& specification);
        ~Engine();

        void run();

        void on_event(Event& event);

        void push_layer(Layer* layer);
        void push_overlay(Layer* layer);

        void close_engine() { _running = false; }

        void resize_viewport(unsigned int width, unsigned int height);

        inline static Engine* get_instance() { return _instance; }
        inline const EngineSpecification& get_specifications() const& { return _specs; }
        inline EngineMetrics get_metrics() const { return _metrics; }
        inline Window& get_window() const { return *_window; }
        inline Viewport& get_viewport() const { return *_viewport; }
        inline Framebuffer& get_framebuffer() const { return _viewport->get_framebuffer(); }
    private:
        static Engine* _instance;
        bool _running = true;
        bool _paused = false;

        EngineSpecification _specs;
        EngineMetrics _metrics;

        Scope<Window> _window;
        Scope<Viewport> _viewport;

        LayerStack _layer_stack;
#ifndef DISABLE_IMGUI
        imgui::ImGuiLayer* _imgui_layer;
#endif // DISABLE_IMGUI

        TimeValue _last_frame_time;
        TimeValue _fps_previous_time;
        int _frame_count;

        bool on_window_close(WindowCloseEvent& event);
        bool on_key_pressed(KeyPressedEvent& event);

        void time_calculations();
    };

    extern Engine* create_engine(EngineCommandLineArgs args);
}
