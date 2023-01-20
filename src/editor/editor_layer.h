#pragma once 

#include "core/rendering/layers/layer.h"

namespace engine {
    class EditorLayer: public Layer {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        virtual void on_imgui_render() override;
    };
}
