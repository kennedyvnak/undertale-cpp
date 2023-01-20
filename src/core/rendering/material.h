#pragma once

#include "core/base.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

// TODO: default values
namespace engine {
	class Shader;
	class Texture;

	class Material {
	private:
		Ref<Shader> _shader;

		std::unordered_map<std::string, int> _uniforms_int;
		std::unordered_map<std::string, float> _uniforms_float;
		std::unordered_map<std::string, glm::vec2> _uniforms_vector2;
		std::unordered_map<std::string, glm::vec3> _uniforms_vector3;
		std::unordered_map<std::string, glm::vec4> _uniforms_vector4;
		std::unordered_map<std::string, glm::mat4> _uniforms_matrix;
		std::unordered_map<std::string, Ref<Texture>> _uniforms_texture;

	public:
		Material(Ref<Shader> shader);
		Material(const Material& other);
		~Material();

#define GET_UNIFORM_VALUE(map, default_return) \
	const auto& search = map.find(name);\
	if (search != map.end())\
		return search->second;\
	return default_return;\

		inline int get_int(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_int, 0) }
		inline float get_float(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_float, 0.0f) }
		inline glm::vec2 get_vector2(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_vector2, glm::vec2(0.0f)) }
		inline glm::vec3 get_vector3(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_vector3, glm::vec3(0.0f)) }
		inline glm::vec4 get_vector4(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_vector4, glm::vec4(0.0f)) }
		inline glm::mat4 get_matrix(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_matrix, glm::mat4(1.0f)) }
		inline Ref<Texture> get_texture(const std::string& name) const { GET_UNIFORM_VALUE(_uniforms_texture, nullptr) }

		inline void set_int(const std::string& name, int value) { _uniforms_int[name] = value; }
		inline void set_float(const std::string& name, float value) { _uniforms_float[name] = value; }
		inline void set_vector2(const std::string& name, const glm::vec2& value) { _uniforms_vector2[name] = value; }
		inline void set_vector3(const std::string& name, const glm::vec3& value) { _uniforms_vector3[name] = value; }
		inline void set_vector4(const std::string& name, const glm::vec4& value) { _uniforms_vector4[name] = value; }
		inline void set_matrix(const std::string& name, const glm::mat4& value) { _uniforms_matrix[name] = value; }
		inline void set_texture(const std::string& name, Ref<Texture> value) { _uniforms_texture[name] = value; }

#undef GET_UNIFORM_VALUE

		void bind() const;
		void unbind() const;

		inline Shader* get_shader() const { return _shader.get(); }
		void set_shader(Ref<Shader> shader);
	};
}
