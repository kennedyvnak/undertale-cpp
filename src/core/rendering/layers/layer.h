#pragma once

#include "core/base.h"

namespace engine {
    class Layer {
    public:
        Layer(const std::string& name = "layer");
        virtual ~Layer() = default;

        virtual void on_attach() {}
        virtual void on_detach() {}
        virtual void on_update() {}
        virtual void on_imgui_render() {}

        inline const std::string& get_name() const { return _name; }
    protected:
        std::string _name;
    };
}