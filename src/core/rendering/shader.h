#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource {
	std::string vertex_source;
	std::string fragment_source;
};

class Shader {
private:
	std::string _filepath;
	unsigned int _id;
	std::unordered_map<std::string, int> _uniform_location_cache;

	ShaderProgramSource parse_shader(const std::string& filename);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader(const std::string& vert_shader_source, const std::string& frag_shader_source);
	
	int get_uniform_location(const std::string& name);

public:
	Shader(const std::string& filename);
	~Shader();

	void bind() const;
	void unbind() const;

	void set_uniform1i(const std::string& name, int value);
	void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};
