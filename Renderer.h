#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void Draw(const VertexArray& va, const Shader& shader) const;
	inline void Clear() const { glClear(GL_COLOR_BUFFER_BIT); }
};

