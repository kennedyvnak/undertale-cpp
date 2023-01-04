#pragma once

#include <memory>
#include "vertex_array.h"
#include "shader.h"
#include "index_buffer.h"
#include "mesh.h"
#include "material.h"

class Renderer {
public:
	void draw(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat) const;
	void clear() const;
};

