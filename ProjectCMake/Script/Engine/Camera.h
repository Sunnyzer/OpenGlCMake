#pragma once
#include <glm\ext\vector_float3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	void ComputeMatricesFromInputs(float _deltaTime);
	static Camera* currentCamera;
	inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	inline glm::vec3 GetPosition() { return position; }
	inline glm::vec3 GetForward() const { return forward; }
	inline void AddScrollValue(float _value) { scrollRatio += _value;  }
private:
	float mouseSpeed = 4.f;
	float speed = 15.0f;
	float initialFoV = 90.0f;
	float verticalAngle = 0.0f;
	float horizontalAngle = 1.6f;
	float scrollRatio = 0;
	float scrollSpeed = 3;
	glm::vec2 lastCursorPosition;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 position = glm::vec3(-10, 3, 0);
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};