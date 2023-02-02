#include "enpch.h"
#include "texture_renderer.h"
#include "core/assets/asset_database.h"
#include "core/rendering/rendering_api.h"
#include "core/rendering/renderer.h"

namespace engine::entities {
	TextureRenderer::TextureRenderer()
		: _texture(nullptr), _transform(), _color(1.0f) {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture)
		: _texture(texture), _transform(), _color(1.0f) {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture, const Transform& transform)
		: _texture(texture), _transform(transform), _color(1.0f) {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture, const Transform& transform, glm::vec4 color)
		: _texture(texture), _transform(transform), _color(color) {
	}

	TextureRenderer::~TextureRenderer() { }

	void TextureRenderer::draw() {
		Renderer::draw_quad(_transform, _texture, _color);
	}

	void TextureRenderer::set_position(glm::vec2 position) { _transform.set_position(position); }
	void TextureRenderer::set_scale(glm::vec2 scale) { _transform.set_scale(scale); }
	void TextureRenderer::set_rotation(float rotation) { _transform.set_rotation(rotation); }
	void TextureRenderer::set_color(glm::vec4 color) { _color = color; }
}
