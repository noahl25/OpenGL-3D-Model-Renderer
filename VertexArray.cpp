#include "VertexArray.h"

VertexArray::VertexArray()
	: m_ElemCount(0)
{

	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);

}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned offset = 0;
	for (unsigned i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, (element.normalized ? GL_TRUE : GL_FALSE), layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	Bind();
	ib.Bind();
	m_ElemCount = ib.GetCount();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
