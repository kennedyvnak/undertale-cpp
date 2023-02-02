#if ENGINE_PLAYER
#pragma once

#include <coal_engine.h>

namespace engine::player {
    class PlayerLayer: public Layer {
    public:
        PlayerLayer(const std::string& name);

        virtual void on_attach() override;
        virtual void post_render() override;
    private:
        Ref<VertexArray> framebuffer_va;
        Ref<VertexBuffer> framebuffer_vb;
        Ref<IndexBuffer> framebuffer_ib;
        Ref<Shader> framebuffer_shader;
    };
}
#endif