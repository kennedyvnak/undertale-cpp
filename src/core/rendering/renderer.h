#pragma once

#include "vertex_array.h"
#include "shader.h"
#include "index_buffer.h"
#include "mesh.h"
#include "material.h"

class Renderer {
public:
	void draw(const Mesh& mesh, const Material& mat) const;
	void clear() const;
};

