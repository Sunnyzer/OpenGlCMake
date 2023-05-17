#include "World.h"
#include <Common\shader.hpp>
#include <Windows.h>
#include "Physics.h"
#include "GameObject.h"
#include <TimerManager.h>
#include <Camera.h>
#include "OnlineNetwork.h"
#include "Cursor.h"
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Marble.h>
#include <Debug.h>
#include <Collider.h>

World* World::world = new World();

void World::ResetObjectSelect(GameObject* _object)
{
	gameObjectSelect = nullptr;
	
}
void World::SelectObject(GameObject* _object)
{
	if (gameObjectSelect)
		gameObjectSelect->OnDestroy.Remove(this, &World::ResetObjectSelect);
	gameObjectSelect = _object;
	if (gameObjectSelect)
		gameObjectSelect->OnDestroy.Add(this, &World::ResetObjectSelect);
}

World::World()
{
	matrixID = 0;
	deltaTime = 0;
	gameObjectAmount = 0;
	gameObjectName = "";
}
World::~World()
{
	size_t i = 0;
	size_t _size = objects.size();
	for (; i < _size; ++i)
	{
		delete objects[i];
	}
	objects.clear();
}

void World::DetailsWindow()
{
	ImGui::Begin("Details", 0);
	ImGui::Text("Name : ");
	ImGui::SameLine();
	std::string _tempName = gameObjectName + "##0001";
	ImGui::InputText(_tempName.c_str(), gameObjectName.data(), 25);
	if (ImGui::Button("Spawn GameObject"))
	{
		if (std::strncmp(gameObjectName.data(), "", 25) == 0)
			gameObjectSelect = new GameObject();
		else
			gameObjectSelect = new GameObject(gameObjectName);
		
		gameObjectSelect->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	}
	if (!gameObjectSelect)
	{
		ImGui::End();
		return;
	}
	ImGui::SeparatorText("Component");
	gameObjectSelect->OnGUI();
	auto _factory = FACTORY(MonoBehaviour).GetFactory();
	size_t _size = _factory.size();
	for (auto _item : _factory)
	{
		if (ImGui::Button(_item.first.c_str()))
		{
			MonoBehaviour* _mono = _item.second;
			gameObjectSelect->AddComponent(_mono);
			Debug::LogWarning("Add " + _item.first);
		}
	}
	ImGui::End();
}
void World::SceneWindow()
{
	ImGui::Begin("Scene", 0);
	std::vector<const char*> names;
	int _count = objects.size();
	for (size_t i = 0; i < _count; ++i)
	{
		names.push_back(objects[i]->name.c_str());
	}
	if (_count <= 0)
	{
		ImGui::End();
		return;
	}
	if (ImGui::ListBox("Objects", &currentSelected, names.data(), _count))
	{
		SelectObject(objects[currentSelected]);
	}
	ImGui::End();
}

void World::GameLoop()
{
	bool _exit = false;
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	matrixID = glGetUniformLocation(programID, "MVP");
	GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");

	Input::BindInput(GLFW_KEY_ESCAPE, InputType::Pressed, [&]() { _exit = true; });
	Input::BindInput(GLFW_KEY_1, InputType::Pressed, OnlineNetwork::onlineNetwork, &OnlineNetwork::LoadClient);
	Input::BindInput(GLFW_KEY_2, InputType::Pressed, OnlineNetwork::onlineNetwork, &OnlineNetwork::LoadServer);
	Input::BindInput(GLFW_MOUSE_BUTTON_LEFT, InputType::Repeat, [&] 
		{ 
			HitResult _hitResult;
			if (Physics::Raycast(Camera::currentCamera->GetPosition(), Camera::currentCamera->GetForward(), _hitResult))
			{
				SelectObject(_hitResult.colliderHit->gameObject);
			}
			else
			{
				Debug::LogWarning("Nothing Hit");
			}
		});

	Camera camera;
	double waitTime = 0;
	double lastTime = 0;
	double currentTime = 0;
	Cursor::Enable();
	do 
	{

		lastTime = currentTime;
		currentTime = glfwGetTime();
		
		deltaTime = float(currentTime - lastTime);
		waitTime += deltaTime;
		bool _tick = waitTime >= PERIOD;

		TimerManager::UpdateTimer(deltaTime);
		Input::UpdateInput();

		if (!_tick) continue;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ComputeMatricesFromInputs(deltaTime);
		glUseProgram(programID);
		OnlineNetwork::onlineNetwork->Update();

		//Window ImGui Update
		DetailsWindow();
		SceneWindow();
		Debug::OnGui();

		for (size_t i = 0; i < gameObjectAmount; ++i)
		{
			GameObject* _object = objects[i];
			_object->Update(deltaTime);
		}
		Physics::UpdatePhysics();

		Render();

		waitTime = 0;
	}
	while (!_exit && glfwWindowShouldClose(WindowGL::window) == 0);
	glDeleteProgram(programID);
}

void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
	++gameObjectAmount;
	currentSelected = gameObjectAmount - 1;
}
void World::RemoveObject(GameObject* _object)
{
	std::vector<GameObject*>::iterator it = objects.begin();
	for (; it != objects.end(); ++it)
	{
		if (*it != _object) continue;
		objects.erase(it);
		--gameObjectAmount;
		return;
	}
}

void World::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(WindowGL::window);
}
