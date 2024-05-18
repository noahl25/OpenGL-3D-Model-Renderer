#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	glCall(glDrawElements(GL_TRIANGLES, va.GetCount(), GL_UNSIGNED_INT, nullptr));

}
