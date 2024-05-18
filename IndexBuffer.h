#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IndexBuffer
{

private:

	unsigned m_RendererID;
	unsigned m_Count;

public:

	IndexBuffer(const uint32_t* data, unsigned count);
	~IndexBuffer();
	
	void Bind() const;
	void Unbind() const;

	inline unsigned GetCount() const { return m_Count; }

};

