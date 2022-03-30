// Include GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"
//#include <Script\WindowGL.h>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 10.0f; // 10 units / second
float mouseSpeed = 0.004f;

void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	//glfwGetCursorPos(WindowGL::window, &xpos, &ypos);

	// Reset mouse position for next frame
	//glfwSetCursorPos(WindowGL::window, WindowGL::GetWidth() /2, WindowGL::GetHeight() /2);

	// Compute new orientation
	//horizontalAngle += mouseSpeed * float(WindowGL::GetWidth() /2 - xpos );
	//verticalAngle   += mouseSpeed * float(WindowGL::GetHeight() /2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	glm::vec3 up = glm::cross( right, direction );
	/*if (KeyPressed(GLFW_KEY_W)){
		position += direction * deltaTime * speed;
	}
	if (KeyPressed(GLFW_KEY_S)){
		position -= direction * deltaTime * speed;
	}
	if (KeyPressed(GLFW_KEY_D)){
		position += right * deltaTime * speed;
	}
	if (KeyPressed(GLFW_KEY_A)){
		position -= right * deltaTime * speed;
	}
	if (KeyPressed(GLFW_KEY_E)) {
		position += glm::vec3(0, 1, 0) * deltaTime * speed;
	}
	if (KeyPressed(GLFW_KEY_Q)) {
		position -= glm::vec3(0, 1, 0) * deltaTime * speed;
	}*/
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 16.0f / 9.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}