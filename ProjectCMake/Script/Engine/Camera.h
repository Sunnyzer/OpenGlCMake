#pragma once
#include <glm\ext\vector_float3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	void ComputeMatricesFromInputs();
	static glm::vec3 forward;
	inline static glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline static glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
private:
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;

	float mouseSpeed = 0.004f;
	float speed = 15.0f;
	float initialFoV = 90.0f;
	float verticalAngle = 0.0f;
	float horizontalAngle = 1.6f;
	glm::vec3 position = glm::vec3(-10, 3, 0);
};