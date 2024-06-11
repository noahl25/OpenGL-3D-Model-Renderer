#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
private:

	unsigned m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	int m_CurrentSlot;

public:

	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned slot = 0);
	void Unbind() const;
	void BindCurrent() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

