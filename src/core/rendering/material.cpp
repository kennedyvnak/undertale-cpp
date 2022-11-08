#include "material.h"

Material::Material(const Shader& shader) 
	: _shader(shader) { }

void Material::bind() const {
}
