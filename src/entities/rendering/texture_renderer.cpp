#include "enpch.h"
#include "texture_renderer.h"
#include "core/assets/asset_database.h"

namespace engine::entities {
	Ref<Material> TextureRenderer::get_default_material() {
		return create_ref<Material>(AssetDatabase::load_shader("res/shaders/default.shader"));
	}

	TextureRenderer::TextureRenderer()
		: _texture(nullptr), _material(get_default_material()), _mesh(Mesh::make_quad_mesh()), _transform() {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture)
		: _texture(texture), _material(get_default_material()), _mesh(Mesh::make_quad_mesh()), _transform() {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture, const Transform& transform)
		: _texture(texture), _material(get_default_material()), _mesh(Mesh::make_quad_mesh()), _transform(transform) {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture, Ref<Material> material)
		: _texture(texture), _material(material), _mesh(Mesh::make_quad_mesh()), _transform() {
	}

	TextureRenderer::TextureRenderer(Ref<Texture> texture, Ref<Material> material, const Transform& transform)
		: _texture(texture), _material(material), _mesh(Mesh::make_quad_mesh()), _transform(transform) {
	}

	TextureRenderer::~TextureRenderer() { }

	void TextureRenderer::set_position(glm::vec2 position) { _transform.set_position(position); }
	void TextureRenderer::set_scale(glm::vec2 scale) { _transform.set_scale(scale); }
	void TextureRenderer::set_rotation(float rotation) { _transform.set_rotation(rotation); }

	void TextureRenderer::draw(Ref<Camera> cam) {
		_material->set_matrix("u_MVP", cam->get_view_projection() * _transform.get_matrix());
		_material->set_texture("u_Texture", _texture);
		_mesh->draw(_material);
	}
}
