#pragma once

#include <GLFW/glfw3.h>

#include "Debug.h"

class Input {

public:

	static void Init(GLFWwindow* w) {
		if (w == nullptr) ASSERT(false);
		window = w;
	}

	static bool GetKey(int key) {
		if (window == nullptr) ASSERT(false);
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	static bool GetMouseButton(int button) {
		if (window == nullptr) ASSERT(false);
		return glfwGetMouseButton(window, button);
	}

	static glm::vec2 GetMousePos() {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	static GLFWwindow* ActiveWindow() {
		return window;
	}

private:

	static inline GLFWwindow* window = nullptr;

};