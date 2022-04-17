#pragma once
#include <glm\ext\vector_float3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	void ComputeMatricesFromInputs();
	glm::vec3 forward;
	static Camera* currentCamera;
	inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	inline glm::vec3 GetPosition() { return position; }
private:
	float mouseSpeed = 0.004f;
	float speed = 1000005.0f;
	float initialFoV = 90.0f;
	float verticalAngle = 0.0f;
	float horizontalAngle = 1.6f;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 position = glm::vec3(-10, 3, 0);
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};