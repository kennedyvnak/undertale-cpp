#pragma once

#include <string>
#include "core/base.h"
#include "core/rendering/layers/layer_stack.h"
#include "imgui/imgui_layer.h"
#include "editor/editor_layer.h"
#include "core/rendering/window.h"

namespace engine {
    class Layer;

    struct EngineCommandLineArgs {
        int count = 0;
        char** args = nullptr;

        const char* operator[](int index) const {
            ASSERT(index < count, "Index out of range.");
            return args[index];
        }
    };

    struct EngineSpecification {
        std::string name;
        EngineCommandLineArgs command_line_args;
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
        inline Window& get_window() { return *_window; }
    private:
        static Engine* _instance;
        Scope<Window> _window;
        EngineSpecification _specs;
        LayerStack _layer_stack;
        imgui::ImGuiLayer* _imgui_layer;
        EditorLayer* _editor_layer;
    };
}
