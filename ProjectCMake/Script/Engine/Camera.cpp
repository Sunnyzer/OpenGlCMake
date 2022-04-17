#include "Camera.h"
#include "World.h"
#include "WindowGL.h"
#include <glm\gtx\quaternion.hpp>
#include "Input.h"

Camera* Camera::currentCamera = nullptr;

Camera::Camera()
{
	projectionMatrix = glm::mat4(1);
	viewMatrix = glm::mat4(1);
	forward = glm::vec3(0);
	right = glm::vec3(0);
	direction = glm::vec3(0);
	currentCamera = this;
	Input::BindInput(GLFW_KEY_W, InputType::Repeat, [&] { position += direction * World::world->deltaTime * speed; });
	Input::BindInput(GLFW_KEY_S, InputType::Repeat, [&] { position -= direction * World::world->deltaTime * speed; });
	Input::BindInput(GLFW_KEY_D, InputType::Repeat, [&] { position += right * World::world->deltaTime * speed; });
	Input::BindInput(GLFW_KEY_A, InputType::Repeat, [&] { position -= right * World::world->deltaTime * speed; });
	Input::BindInput(GLFW_KEY_E, InputType::Repeat, [&] { position += glm::vec3(0, 1, 0) * World::world->deltaTime * speed; });
	Input::BindInput(GLFW_KEY_Q, InputType::Repeat, [&] { position -= glm::vec3(0, 1, 0) * World::world->deltaTime * speed; });
}

void Camera::ComputeMatricesFromInputs()
{
	double xpos, ypos;
	glfwGetCursorPos(WindowGL::window, &xpos, &ypos);
	glfwSetCursorPos(WindowGL::window, WindowGL::GetWidth() / 2, WindowGL::GetHeight() / 2);
	horizontalAngle += mouseSpeed * float(WindowGL::GetWidth() / 2 - xpos);
	verticalAngle += mouseSpeed * float(WindowGL::GetHeight() / 2 - ypos);
	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
	glm::vec3 up = glm::cross(right, direction);
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projectionMatrix = glm::perspective(glm::radians(FoV), 16.0f / 9.0f, 0.1f, 100.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(position,/*Camera is here*/position + direction, /*and looks here : at the same position, plus "direction"*/up /*Head is up (set to 0,-1,0 to look upside-down*/);
	// For the next frame, the "last time" will be "now"
	forward = direction;
}