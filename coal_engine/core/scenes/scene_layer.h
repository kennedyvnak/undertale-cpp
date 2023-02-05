#pragma once

#include "core/rendering/layers/layer.h"
#include "entities/rendering/texture_renderer.h"
#include "core/events/engine_event.h"

namespace engine {
    class SceneLayer: public Layer {
    public:
        SceneLayer(const std::string& name = "scene_layer")
            : Layer(name) {}

        virtual void on_attach() override;
        virtual void on_update() override;
        virtual void render() override;
        virtual bool on_event(Event& event) override;
    private:
        Ref<Camera> _camera;
        std::vector<Scope<entities::TextureRenderer>> _texture_renderers;

        bool on_resize_viewport(EngineResizeViewportEvent& event);
    };
}