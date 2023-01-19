#pragma once

#include "enpch.h"
#include "core/base.h"

namespace engine {
    class Window;

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
        ~Engine();

        void run();

        static Engine* create_engine(EngineCommandLineArgs args);

        inline Engine* get_instance() { return _instance; }
        inline const EngineSpecification& get_specifications() const& { return _specs; }
        inline Window& get_window() { return *_window; }

    private:
        static Engine* _instance;
        Scope<Window> _window;
        EngineSpecification _specs;
    };
}