#pragma once 

#include <coal_engine.h>
#include "game_view_window.h"

namespace engine::editor {
    class EditorLayer: public Layer {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        virtual void on_imgui_render() override;
    private:
        Scope<GameViewWindow> _game_view_window;
    };
}
