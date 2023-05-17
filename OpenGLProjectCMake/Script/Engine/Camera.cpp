#include "Camera.h"
#include <glm\gtx\quaternion.hpp>
#include "World.h"
#include "WindowGL.h"
#include "Input.h"
#include <Cursor.h>

Camera* Camera::currentCamera = nullptr;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::currentCamera->AddScrollValue((float)yoffset);
}

Camera::Camera()
{
	projectionMatrix = glm::mat4(1);
	viewMatrix = glm::mat4(1);
	forward = glm::vec3(0);
	right = glm::vec3(0);
	up = glm::vec3(0);
	lastCursorPosition = glm::vec3(0);
	currentCamera = this;
	Input::BindInput(GLFW_MOUSE_BUTTON_RIGHT, InputType::Pressed, [] { currentCamera->canMove = true; Cursor::Lock(); });
	Input::BindInput(GLFW_MOUSE_BUTTON_RIGHT, InputType::Released, [] { currentCamera->canMove = false;  Cursor::Enable(); });

	Input::BindInput(GLFW_KEY_W, InputType::Repeat, [&] { if (canMove) position += forward * World::world->GetDeltaTime() * speed; });
	Input::BindInput(GLFW_KEY_S, InputType::Repeat, [&] { if (canMove) position -= forward * World::world->GetDeltaTime() * speed; });
	Input::BindInput(GLFW_KEY_D, InputType::Repeat, [&] { if (canMove) position += right * World::world->GetDeltaTime() * speed; });
	Input::BindInput(GLFW_KEY_A, InputType::Repeat, [&] { if (canMove) position -= right * World::world->GetDeltaTime() * speed; });
	Input::BindInput(GLFW_KEY_E, InputType::Repeat, [&] { if (canMove) position += up * World::world->GetDeltaTime() * speed; });
	Input::BindInput(GLFW_KEY_Q, InputType::Repeat, [&] { if (canMove) position -= up * World::world->GetDeltaTime() * speed; });
	glfwSetScrollCallback(WindowGL::window, scroll_callback);
}

void Camera::ComputeMatricesFromInputs(float _deltaTime)
{
	glm::vec2 _cursorPosition = lastCursorPosition;
	if (canMove)
		_cursorPosition = Cursor::GetCursorPosition();
	horizontalAngle += mouseSpeed/1000 * float(lastCursorPosition.x - _cursorPosition.x);
	verticalAngle += mouseSpeed/1000 * float(lastCursorPosition.y - _cursorPosition.y);
	float _angle = cos(verticalAngle);
	forward = glm::vec3(_angle * sin(horizontalAngle), sin(verticalAngle), _angle * cos(horizontalAngle));
	right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
	up = glm::cross(right, forward);
	// Projection matrix : 16 : 9 ratio
	projectionMatrix = glm::perspective(glm::radians(initialFoV - scrollRatio * scrollSpeed), 16.0f / 9.0f, 0.1f, 100.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(position,/*Camera position*/position + forward, /*and looks here plus "direction"*/ up/*Head is up*/);
	//store last cursor position
	lastCursorPosition = canMove ? _cursorPosition : Cursor::GetCursorPosition();
}