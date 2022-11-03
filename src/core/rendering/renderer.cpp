#include "renderer.h"

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.bind();
    va.bind();
    ib.bind();

    GL_CALL(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
