#pragma once 

#include "core/rendering/layers/layer.h"
#include "game_view_window.h"
#include "core/base.h"

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
