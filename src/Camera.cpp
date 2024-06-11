#include "Camera.h"

static float cameraFOV = 60.0f;
static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	cameraFOV -= (float)yoffset;
	if (cameraFOV < 1.0f)
		cameraFOV = 1.0f;
	if (cameraFOV > 90.0f)
		cameraFOV = 90.0f;
}

void Camera::Update(float deltaTime)
{
	if (m_FirstUpdate) {
		m_FirstUpdate = false;
		glfwSetScrollCallback(Input::ActiveWindow(), &glfwScrollCallback);
	}

	MoveCamera(deltaTime);
	RotateCamera(deltaTime);

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraDirection, m_CameraUp);
}
 
glm::mat4 Camera::GetProjectionMatrix()
{
 
	return glm::perspective(glm::radians(cameraFOV), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::MoveCamera(float deltaTime)
{
	float scaledCameraSpeed = (Input::GetKey(GLFW_KEY_LEFT_SHIFT) ? m_FastCameraSpeed : m_CameraSpeed) * deltaTime;

	if (Input::GetKey(GLFW_KEY_W)) {
		m_CameraPos += scaledCameraSpeed * m_CameraDirection;
	}
	else if (Input::GetKey(GLFW_KEY_S)) {
		m_CameraPos -= scaledCameraSpeed * m_CameraDirection;
	}
	if (Input::GetKey(GLFW_KEY_D)) {
		m_CameraPos += glm::normalize(glm::cross(m_CameraDirection, m_CameraUp)) * scaledCameraSpeed;
	}
	else if (Input::GetKey(GLFW_KEY_A)) {
		m_CameraPos -= glm::normalize(glm::cross(m_CameraDirection, m_CameraUp)) * scaledCameraSpeed;
	}
	if (Input::GetKey(GLFW_KEY_E)) {
		m_CameraPos += scaledCameraSpeed * m_CameraUp;
	}
	else if (Input::GetKey(GLFW_KEY_Q)) {
		m_CameraPos -= scaledCameraSpeed * m_CameraUp;
	}
}

void Camera::RotateCamera(float deltaTime)
{
	float scaledMouseSensitivity = m_MouseSensitivity * deltaTime;

	if (Input::GetMouseButton(GLFW_MOUSE_BUTTON_1)) {

		if (!m_InWindow) {
			m_LastMousePos = Input::GetMousePos();
		}

		m_InWindow = true;
		glfwSetInputMode(Input::ActiveWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glm::vec2 difference = Input::GetMousePos() - m_LastMousePos;
		m_Yaw += difference.x * scaledMouseSensitivity;
		m_Pitch -= difference.y * scaledMouseSensitivity;
		m_LastMousePos = Input::GetMousePos();
	}
	else {
		glfwSetInputMode(Input::ActiveWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_InWindow = false;
	}


	m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

	m_CameraDirection.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	m_CameraDirection.y = glm::sin(glm::radians(m_Pitch));
	m_CameraDirection.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));

	m_CameraDirection = glm::normalize(m_CameraDirection);
}

