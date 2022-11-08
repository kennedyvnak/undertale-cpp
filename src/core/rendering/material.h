#pragma once

#include "shader.h"

class Material {
private:
	Shader _shader;

public:
	Material(const Shader& shader);
	void bind() const;

	inline const Shader& get_shader() const& { return _shader; }
	void set_shader(const Shader& shader) { _shader = shader; }
};

