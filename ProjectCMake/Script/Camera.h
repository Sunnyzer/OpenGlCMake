#pragma once
#include <glm\ext\vector_float3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	void ComputeMatricesFromInputs();
	
	inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float mouseSpeed = 0.004f;
	float speed = 10.0f;
	float initialFoV = 45.0f;
	float verticalAngle = 0.0f;
	float horizontalAngle = 3.14f;
	glm::vec3 position = glm::vec3(0, 0, 5);
};