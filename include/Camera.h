#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"

class Camera
{
public:
	
	void Update(float deltaTime);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

private:

	void MoveCamera(float deltaTime);
	void RotateCamera(float deltaTime);
	void ZoomCamera(float deltaTime);

private:

	const glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_CameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec2 m_LastMousePos;
	bool m_InWindow = false;

	float m_Pitch = 0.0f, m_Yaw = 0.0f;

	const float m_CameraSpeed = 1.0f;
	const float m_FastCameraSpeed = m_CameraSpeed * 3;
	const float m_MouseSensitivity = 2.0f;

	bool m_FirstUpdate = true;


};

