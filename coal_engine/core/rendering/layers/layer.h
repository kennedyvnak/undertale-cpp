#pragma once

#include "core/base.h"
#include "core/events/event.h"

namespace engine {
    class Layer {
    public:
        Layer(const std::string& name = "layer");
        virtual ~Layer() = default;

        virtual void on_attach() {}
        virtual void on_detach() {}
        virtual void on_update() {}
        virtual void render() {}
        virtual void post_render() {}
#ifndef DISABLE_IMGUI
        virtual void on_imgui_render() {}
#endif

        virtual bool on_event(Event& event) { return false; }

        inline const std::string& get_name() const { return _name; }
    protected:
        std::string _name;
    };
}
