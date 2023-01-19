#include "material.h"
#include "shader.h"
#include "texture.h"

namespace engine {
	Material::Material(Ref<Shader> shader)
		: _shader(shader) { }

	Material::Material(const Material& other) {
		_shader = other._shader;

		_uniforms_int = other._uniforms_int;
		_uniforms_float = other._uniforms_float;
		_uniforms_vector2 = other._uniforms_vector2;
		_uniforms_vector3 = other._uniforms_vector3;
		_uniforms_vector4 = other._uniforms_vector4;
		_uniforms_matrix = other._uniforms_matrix;

	}

	Material::~Material() { }

	void Material::bind() const {
		_shader->bind();
		if (_shader) {
			for (const auto& uniform : _uniforms_int)
				_shader->set_uniform_int(uniform.first, uniform.second);
			for (const auto& uniform : _uniforms_float)
				_shader->set_uniform_float(uniform.first, uniform.second);
			for (const auto& uniform : _uniforms_vector2)
				_shader->set_uniform_vector2(uniform.first, uniform.second);
			for (const auto& uniform : _uniforms_vector3)
				_shader->set_uniform_vector3(uniform.first, uniform.second);
			for (const auto& uniform : _uniforms_vector4)
				_shader->set_uniform_vector4(uniform.first, uniform.second);
			for (const auto& uniform : _uniforms_matrix)
				_shader->set_uniform_matrix(uniform.first, uniform.second);

			int tex_index = 0;
			for (const auto& uniform : _uniforms_texture) {
				uniform.second->bind(tex_index);
				_shader->set_uniform_int(uniform.first, tex_index);
				tex_index++;
			}
		}
	}

	void Material::unbind() const {
		_shader->unbind();
	}

	void Material::set_shader(Ref<Shader> shader) {
		if (shader)
			_shader = shader;
	}
}