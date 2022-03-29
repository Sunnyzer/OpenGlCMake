#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#define KeyPressed(key) glfwGetKey(WindowGL::window, key) == GLFW_PRESS

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
#endif