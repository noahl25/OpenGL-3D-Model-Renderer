#pragma once

#include <memory>
#include <thread>
#include <filesystem>

#include "VertexArray.h"
#include "Timer.h"
#include "Debug.h"
#include "Shader.h"

class ModelRenderer
{
private:

	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
 
	inline std::pair<int, int> ApproxVertexCount(int fileSize) {
		int verticies = -3.3 * std::pow(10, -10) * fileSize * fileSize + 8.29 * std::pow(10, -3) * fileSize + -6.68;
		int indicies = verticies * 4;
		return { std::max(10, verticies), std::max(20, indicies) };
	}


public:

	ModelRenderer(const char* path);
	~ModelRenderer();

	void Render();
};

