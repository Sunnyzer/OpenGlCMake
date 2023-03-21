
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <time.h>
#include "WindowGL.h"
#include "World.h"
#include "OnlineNetwork.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "MarbleControl.h"
#include "ENet.h"
#include <Debug.h>
#include <Cursor.h>

using namespace glm;

int main(int, char**)
{
	//TODO
	// - Create CursorManager to lock and change visibility etc...

	//Leak Memory debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/*
	Break Point To Alloc 
	_CrtSetBreakAlloc();
	*/  
	//Random with timer
	srand((unsigned int)time(NULL));
	
	if (!glfwInit())
	{
		Debug::LogError("Failed to initialize GLFW !!!");
		char _r = getchar();
		glfwTerminate();
		return -1;
	}
	//CreateWindow 
	WindowGL windowGL;
	windowGL.CreateMyWindow("Ma Game", 1080, 720);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		Debug::LogError("Failed to initialize GLEW !!!");
		char _r = getchar();
		glfwTerminate();
		return -1;
	}
	const char* glsl_version = "#version 330";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.MouseDrawCursor = true;
	ImGui_ImplGlfw_InitForOpenGL(WindowGL::window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	ENet::Initialize();

	glfwSetInputMode(WindowGL::window, GLFW_STICKY_KEYS, GL_TRUE);
	Cursor::Lock();

	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	////Create first gameObject to instanciate the other gameObject
	GameObject* _pool = new GameObject();
	_pool->GetTransform()->SetPosition(vec3(0, -0.5f, 0));
	////Add Component Mesh and MarbleControl to gameObject
	MarbleControl* _marbleControl = _pool->AddComponent<MarbleControl>();
	//Mesh* _mesh = _pool->AddComponent<Mesh>();
	////Load Mesh
	//_mesh->LoadMesh("billard.obj", "Board_UV.bmp", false);
	
	//Start Loop
	World::world->GameLoop();
	
	//Delete Singleton Manager
	delete World::world;
	delete OnlineNetwork::onlineNetwork;

	glDeleteVertexArrays(1, &VertexArrayID);

	//Destroy all remaining glfw resources
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}