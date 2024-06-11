#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "imgui/imgui.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "ModelRenderer.h"
#include "Camera.h"


namespace test {

	class Test {

	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPtr);

		void OnImGuiRender() override;

		template <typename T> void RegisterTest(const char* name) {
			m_Tests.push_back(std::make_pair(std::string(name), []() {return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};

	class TextureTest2D : public Test {
	public:
		TextureTest2D();
		~TextureTest2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		VertexArray m_VAO;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		Shader m_Shader;
		Texture m_Texture;
		glm::vec3 translation = glm::vec3(0.0f);
	};

	class VertexTest : public Test {
	public:
		VertexTest();
		~VertexTest();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:

		struct MeshData {
			std::vector<float> vertexPositions;
			std::vector<uint32_t> indicies;
		};

		VertexArray m_VAO;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		Shader m_Shader;
		Texture m_Texture;
		Texture m_Texture1;

		Camera cam;

		glm::vec3 m_Translation = glm::vec3(0.0f);

		MeshData parseObj(const char* path);
	};

	class ModelRendererTest : public Test {
	public:
		ModelRendererTest();
		~ModelRendererTest();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
 
	private:

		Camera cam;
		Shader m_Shader;
		ModelRenderer m_ModelRenderer;
	};

};
