#include "renderer.h"

void Renderer::draw(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat) const {
    mesh->draw(mat);
}

void Renderer::clear() const {
    GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
