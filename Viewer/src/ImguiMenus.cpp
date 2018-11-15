#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>

bool showDemoWindow = false;
bool showAnotherWindow = false;
bool showCameraWindow = false;
bool showModelWidow = false;

glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor()
{
	return clearColor;
}

void ModelMenu(Scene scene) {
	static float xRotate=0.0f, yRotate=0.0f, zRotate = 0.0f;
	static float xTranslate = 0.0f, yTranslate = 0.0f, zTranslate = 0.0f;
	static float scale = 0.0f;
	static float xPos = 0.0f, yPos = 0.0f,zPos = 0.0f;
	static int prevActiveModel = scene.GetActiveModelIndex();

	if (ImGui::Button("Load Model"))
	{
		nfdchar_t *outPath = NULL;
		nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
		if (result == NFD_OKAY) {
			MeshModel m = Utils::LoadMeshModel(outPath);
			scene.AddModel(std::make_shared<MeshModel>(m));
			free(outPath);
		}
		else if (result == NFD_CANCEL) {
		}
		else {
		}
	}

	if (ImGui::TreeNode("Select Active Model")) {
		std::vector<std::string> modelNames = scene.getModelsNames();
		for (int i = 0; i < (int)modelNames.size(); i++)
		{
			if (ImGui::Selectable(modelNames[i].c_str(), scene.GetActiveModelIndex() == i))
			{
				scene.SetActiveModelIndex(i);
			}
		}
		ImGui::TreePop();
	}

	// CAMERA???????????????????
	ImGui::SliderFloat("Rotate X", &xRotate, -360.0f, 360.0f);
	ImGui::SliderFloat("Rotate Y", &yRotate, -360.0f, 360.0f);
	ImGui::SliderFloat("Rotate Z", &zRotate, -360.0f, 360.0f);
	ImGui::SliderFloat("Translate X", &xTranslate, -135.0f, 135.0f);
	ImGui::SliderFloat("Translate Y", &yTranslate, -100.0f, 100.0f);
	ImGui::SliderFloat("Translate Z", &zTranslate, -100.0f, 100.0f);
	ImGui::SliderFloat("Scale", &scale, 0.0f, 1.0f);

	
	/*if (ImGui::Button("Delete Active Model")) {
		if (scene.getModels().size() > 1)
		{

			scene.setModels(scene.getModels().erase(scene.getModels().begin() + scene.GetActiveModelIndex()));
			scene.SetActiveModelIndex(0);
		}
	}*/
	std::shared_ptr<MeshModel> active=nullptr;
	if (scene.GetActiveModelIndex() != -1)
	{
		active = scene.GetActiveModel();
	}

	/*if (prevActiveModel != scene.GetActiveModelIndex())
	{
		prevActiveModel = scene.GetActiveModelIndex();
		xTranslate = active.get()->getCenter().x;
		yTranslate = active.get()->getCenter().y;
		zTranslate = active.get()->getCenter().z;
	}*/
	if (active != nullptr) {

		if (xTranslate != 0)
		{
			active.get()->setTranslation(Utils::Translation(glm::vec3(xTranslate- active.get()->getCenter().x, 0, 0)));
		}
		if (yTranslate != 0)
		{
			active.get()->setTranslation(Utils::Translation(glm::vec3(0, yTranslate- active.get()->getCenter().y, 0)));
		}
		if (zTranslate != 0)
		{
			active.get()->setTranslation(Utils::Translation(glm::vec3(0, 0, zTranslate- active.get()->getCenter().z)));
		}

		if (xRotate != active.get()->getCenter().z)
		{
			active.get()->setTranslation(Utils::Translation(glm::vec3(0, 0, zTranslate)));
		}
	}
	//scene.updateModel(active, scene.GetActiveModelIndex());
}

void CameraMenu(Scene scene) {


}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	double eye=-1.0,at=-1.0,up=-1.0;
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;
		

		ImGui::Begin("Main Menu");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");    
		ImGui::Checkbox("Show Model Window", &showModelWidow);
		ImGui::Checkbox("Show Camera Window", &showCameraWindow);

		//ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
	//	ImGui::Checkbox("Another Window", &showAnotherWindow);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}
	if (showCameraWindow)
		CameraMenu(scene);
	if (showModelWidow)
		ModelMenu(scene);
	

	// 4. Demonstrate creating a fullscreen menu bar and populating it.
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						MeshModel m = Utils::LoadMeshModel(outPath);
						//m.Translation(1,1,1);
						scene.AddModel(std::make_shared<MeshModel>(m));
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				if (ImGui::MenuItem("Load Camera...","CTRL+C"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						MeshModel m = Utils::LoadMeshModel(outPath);
						//Camera& c = Camera(m.getFaces(),m.getVertices(),m.getNormals(),m.GetModelName(),eye,at,up);
						if(eye!=-1 && at!=-1 && up!=-1)
							//scene.AddCamera(c);
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}