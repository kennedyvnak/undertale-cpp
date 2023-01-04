#pragma once

#include <memory>

class Shader;

class Material {
private:
	std::shared_ptr<Shader> _shader;

public:
	Material(std::shared_ptr<Shader> shader);
	void bind() const;

	std::shared_ptr<Shader> get_shader() const { return _shader; }
	void set_shader(std::shared_ptr<Shader> shader) { _shader = shader; }
};

