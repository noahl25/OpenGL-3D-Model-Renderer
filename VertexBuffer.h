#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{

private:

	unsigned m_RendererID;

public:

	VertexBuffer(const void* data, unsigned size);
	~VertexBuffer();
	
	void Bind() const;
	void Unbind() const;

};

