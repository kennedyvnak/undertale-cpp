#include "enpch.h"
#include "texture_renderer.h"
#include "core/assets/asset_database.h"
#include "core/rendering/rendering_api.h"
#include "core/rendering/renderer.h"
#include "core/os/time.h"
#include "core/os/random.h"

namespace engine::entities {
	TextureRenderer::TextureRenderer(Ref<Texture> texture, const Transform& transform, glm::vec4 color)
		: _texture(texture), _transform(transform), _color(color), _time_offset(Random::range(0.0f, 20.0f)), _time_speed(Random::range(0.75f, 3.0f)), _rotation_speed(Random::range(-80.0f, 80.0f)) {
	}

	TextureRenderer::~TextureRenderer() { }

	static float normalize(const float value, const float start, const float end) {
		const float width = end - start;   // 
		const float offset_value = value - start;   // value relative to 0

		return (offset_value - (floor(offset_value / width) * width)) + start;
		// + start to reset back to start of original range
	}

	void TextureRenderer::update() {
		set_rotation(normalize(_transform.get_rotation() + Time::get_delta_time() * _rotation_speed, 0.0f, 360.0f));
	}

	void TextureRenderer::draw() {
		Renderer::draw_quad(_transform, _texture, _color, _time_offset, _time_speed);
	}

	void TextureRenderer::set_position(glm::vec2 position) { _transform.set_position(position); }
	void TextureRenderer::set_scale(glm::vec2 scale) { _transform.set_scale(scale); }
	void TextureRenderer::set_rotation(float rotation) { _transform.set_rotation(rotation); }
	void TextureRenderer::set_color(glm::vec4 color) { _color = color; }
}
