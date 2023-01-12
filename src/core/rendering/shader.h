#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include "core/assets/asset.h"

struct ShaderProgramSource {
	std::string vertex_source;
	std::string fragment_source;
};

class Shader : public Asset {
private:
	unsigned int _id;
	mutable std::unordered_map<std::string, int> _uniform_location_cache;

	ShaderProgramSource parse_shader(const std::string& filename);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader(const std::string& vert_shader_source, const std::string& frag_shader_source);

	int get_uniform_location(const std::string& name) const;

public:
	Shader(const std::string& filename);
	~Shader();

	void bind() const;
	void unbind() const;

	void set_uniform_int(const std::string& name, int value);
	void set_uniform_float(const std::string& name, float value);
	void set_uniform_vector2(const std::string& name, const glm::vec2& value);
	void set_uniform_vector3(const std::string& name, const glm::vec3& value);
	void set_uniform_vector4(const std::string& name, const glm::vec4& value);
	void set_uniform_matrix(const std::string& name, const glm::mat4& value);
};
