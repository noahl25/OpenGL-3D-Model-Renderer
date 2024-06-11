#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

struct ShadersProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{

private:

	unsigned m_RendererID;
	std::string m_FilePath;

	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	
	Shader(const std::string& file);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, glm::vec4 value);
	void SetUniformMat4(const std::string& name, const glm::mat4& value);

private:
	ShadersProgramSource ParseShader(const std::string& file);
	unsigned CompileShader(unsigned type, const std::string& source);
	unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);

};

