#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debug.h"

struct VertexBufferElement {
	unsigned type;
	unsigned count;
	bool normalized;

	static unsigned GetSizeOfType(unsigned type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:

	std::vector<VertexBufferElement> m_Elements;
	unsigned m_Stride;

public:

	VertexBufferLayout()
		: m_Stride(0) {}

	template <typename T>
	void Push(unsigned count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned count) {
		m_Elements.push_back(VertexBufferElement{GL_FLOAT, count, false});
		m_Stride += sizeof(float) * count;
	}

	template<>
	void Push<unsigned>(unsigned count) {
		m_Elements.push_back(VertexBufferElement{ GL_UNSIGNED_INT, count, false });
		m_Stride += sizeof(unsigned) * count;
	}

	template<>
	void Push<unsigned char>(unsigned count) {
		m_Elements.push_back(VertexBufferElement{ GL_UNSIGNED_BYTE, count, true });
		m_Stride += sizeof(unsigned char) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned GetStride() const { return m_Stride; }

};

