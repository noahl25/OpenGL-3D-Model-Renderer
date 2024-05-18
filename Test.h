#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"

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

};
