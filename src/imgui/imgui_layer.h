#pragma once

#include "core/rendering/layers/layer.h"

namespace engine::imgui {
    class ImGuiLayer: public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void on_attach() override;
        virtual void on_detach() override;

        void begin();
        void end();
    };
}
