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

	void set_uniform1i(const String& name, int value);
	void set_uniform4f(const String& name, float v0, float v1, float v2, float v3);
	void set_uniform_mat4f(const String& name, Matrix matrix);
};
