#include "MovementMarble.h"
#include "WindowGL.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "GameObject.h"
#include "Transform.h"

void MovementMarble::InputMovement(GameObject* _object,float _moveSpeed)
{
	float _x = glfwGetKey(WindowGL::window, GLFW_KEY_UP) == GLFW_PRESS ? 1 : glfwGetKey(WindowGL::window, GLFW_KEY_DOWN) == GLFW_PRESS ? -1 : 0;
	float _y = glfwGetKey(WindowGL::window, GLFW_KEY_RIGHT) == GLFW_PRESS ? 1 : glfwGetKey(WindowGL::window, GLFW_KEY_LEFT) == GLFW_PRESS ? -1 : 0;
	glm::vec3 _direction(_x * _moveSpeed, 0, _y * _moveSpeed);
	_object->GetTransform()->AddPosition(_direction);
}
