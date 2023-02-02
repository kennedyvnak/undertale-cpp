#if ENGINE_EDITOR
#ifdef DISABLE_IMGUI
#error "Engine editor needs imgui"
#endif // DISABLE_IMGUI

#include <coal_engine.h>
#include "editor_gui/editor_layer.h"

namespace engine {
    namespace editor {
        class EngineEditor: public Engine {
        public:
            EngineEditor(const EngineSpecification& specification)
                : Engine(specification) {
                push_layer(new EditorLayer());
            }
        };
    }

    Engine* create_engine(EngineCommandLineArgs args) {
        EngineSpecification specification;
        specification.name = "Coal Engine Editor";
        specification.command_line_args = args;
        return new editor::EngineEditor(specification);
    }
}
#endif // ENGINE_EDITOR
