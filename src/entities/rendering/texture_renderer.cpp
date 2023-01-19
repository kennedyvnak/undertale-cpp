#include "texture_renderer.h"
#include "core/rendering/mesh.h"
#include "core/rendering/material.h"
#include "core/rendering/shader.h"
#include "core/rendering/camera.h"
#include "core/components/transform.h"
#include "core/assets/asset_database.h"

namespace engine::entities {
	std::shared_ptr<Material> TextureRenderer::get_default_material() {
		return std::make_shared<Material>(AssetDatabase::load_shader("res/shaders/default.shader"));
	}

	TextureRenderer::TextureRenderer()
		: _texture(nullptr), _material(get_default_material()), _mesh(Mesh::make_quad_mesh()), _transform() {
	}

	TextureRenderer::TextureRenderer(std::shared_ptr<Texture> texture)
		: _texture(texture), _material(get_default_material()), _mesh(Mesh::make_quad_mesh()), _transform() {
	}

	TextureRenderer::TextureRenderer(std::shared_ptr<Texture> texture, const Transform& transform)
		: _texture(texture), _material(get_default_material()), _mesh(Mesh::make_quad_mesh()), _transform(transform) {
	}

	TextureRenderer::TextureRenderer(std::shared_ptr<Texture> texture, std::shared_ptr<Material> material)
		: _texture(texture), _material(material), _mesh(Mesh::make_quad_mesh()), _transform() {
	}

	TextureRenderer::TextureRenderer(std::shared_ptr<Texture> texture, std::shared_ptr<Material> material, const Transform& transform)
		: _texture(texture), _material(material), _mesh(Mesh::make_quad_mesh()), _transform(transform) {
	}

	TextureRenderer::~TextureRenderer() { }

	void TextureRenderer::set_position(glm::vec2 position) { _transform.set_position(position); }
	void TextureRenderer::set_scale(glm::vec2 scale) { _transform.set_scale(scale); }
	void TextureRenderer::set_rotation(float rotation) { _transform.set_rotation(rotation); }

	void TextureRenderer::draw(std::shared_ptr<Camera> cam) {
		_material->set_matrix("u_MVP", cam->get_view_projection() * _transform.get_matrix());
		_material->set_texture("u_Texture", _texture);
		_mesh->draw(_material);
	}
}
