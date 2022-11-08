#include "renderer.h"

void Renderer::draw(const Mesh& mesh, const Material& mat) const {
    mesh.draw(mat);
}

void Renderer::clear() const {
    GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
