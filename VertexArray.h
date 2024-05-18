#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
private:

	unsigned m_RendererID;
	unsigned m_ElemCount;

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& ib);

	void Bind() const;
	void Unbind() const;

	inline unsigned GetCount() const { return m_ElemCount; }

};

