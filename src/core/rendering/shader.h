#pragma once

#include "engine.h"
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource {
	String vertex_source;
	String fragment_source;
};

class Shader {
private:
	String _filepath;
	unsigned int _id;
	mutable std::unordered_map<String, int> _uniform_location_cache;

	ShaderProgramSource parse_shader(const String& filename);
	unsigned int compile_shader(unsigned int type, const String& source);
	unsigned int create_shader(const String& vert_shader_source, const String& frag_shader_source);
	
	int get_uniform_location(const String& name) const;

public:
	Shader(const String& filename);
	~Shader();

	void bind() const;
	void unbind() const;

	void set_uniform_int(const String& name, int value);
	void set_uniform_float(const String& name, float value);
	void set_uniform_vector2(const String& name, const Vector2& value);
	void set_uniform_vector3(const String& name, const Vector3& value);
	void set_uniform_vector4(const String& name, const Vector4& value);
	void set_uniform_matrix(const String& name, const Matrix& value);
};
