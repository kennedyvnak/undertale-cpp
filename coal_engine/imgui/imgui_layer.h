#ifndef DISABLE_IMGUI
#pragma once

#include "core/rendering/layers/layer.h"

namespace engine::imgui {
    class ImGuiLayer: public Layer {
    public:
        const char* ini_load_path = "res/layouts/default.ini";
        const char* ini_config_path = "config/imgui.ini";

        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void on_attach() override;
        virtual void on_detach() override;

        void begin();
        void end();
    };
}
#endif // DISABLE_IMGUI