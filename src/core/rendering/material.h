#pragma once

#include <memory>
#include <unordered_map>
#include "engine.h"
#include <iostream>

class Shader;
class Texture;

// TODO: default values

class Material {
private:
	std::shared_ptr<Shader> _shader;

	std::unordered_map<std::string, int> _uniforms_int;
	std::unordered_map<std::string, float> _uniforms_float;
	std::unordered_map<std::string, Vector2> _uniforms_vector2;
	std::unordered_map<std::string, Vector3> _uniforms_vector3;
	std::unordered_map<std::string, Vector4> _uniforms_vector4;
	std::unordered_map<std::string, Matrix> _uniforms_matrix;
	std::unordered_map<std::string, std::shared_ptr<Texture>> _uniforms_texture;

public:
	Material(std::shared_ptr<Shader> shader);
	Material(const Material& other);
	~Material();

#define GET_UNIFORM_VALUE(map, default_return) \
	const auto& search = map.find(name);\
	if (search != map.end())\
		return search->second;\
	return default_return;\

	inline int get_int(const String& name) const { GET_UNIFORM_VALUE(_uniforms_int, 0) }
	inline float get_float(const String& name) const { GET_UNIFORM_VALUE(_uniforms_float, 0.0f) }
	inline Vector2 get_vector2(const String& name) const { GET_UNIFORM_VALUE(_uniforms_vector2, Vector2(0.0f)) }
	inline Vector3 get_vector3(const String& name) const { GET_UNIFORM_VALUE(_uniforms_vector3, Vector3(0.0f)) }
	inline Vector4 get_vector4(const String& name) const { GET_UNIFORM_VALUE(_uniforms_vector4, Vector4(0.0f)) }
	inline Matrix get_matrix(const String& name) const { GET_UNIFORM_VALUE(_uniforms_matrix, Matrix(1.0f)) }
	inline std::shared_ptr<Texture> get_texture(const String& name) const { GET_UNIFORM_VALUE(_uniforms_texture, nullptr) }

	inline void set_int(const String& name, int value) { _uniforms_int[name] = value; }
	inline void set_float(const String& name, float value) { _uniforms_float[name] = value; }
	inline void set_vector2(const String& name, const Vector2& value) { _uniforms_vector2[name] = value; }
	inline void set_vector3(const String& name, const Vector3& value) { _uniforms_vector3[name] = value; }
	inline void set_vector4(const String& name, const Vector4& value) { _uniforms_vector4[name] = value; }
	inline void set_matrix(const String& name, const Matrix& value) { _uniforms_matrix[name] = value; }
	inline void set_texture(const String& name, std::shared_ptr<Texture> value) { _uniforms_texture[name] = value; }

#undef GET_UNIFORM_VALUE

	void bind() const;
	void unbind() const;

	inline Shader* get_shader() const { return _shader.get(); }
	void set_shader(std::shared_ptr<Shader> shader);
};

