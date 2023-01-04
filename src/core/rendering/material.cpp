#include "material.h"

Material::Material(std::shared_ptr<Shader> shader)
	: _shader(shader) { }

void Material::bind() const {
}
