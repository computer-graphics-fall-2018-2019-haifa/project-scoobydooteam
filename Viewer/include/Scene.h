#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"

/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
public:
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Camera> cameras;

	int activeCameraIndex;
	int activeModelIndex;

public:
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& model);
	const int GetModelCount() const;
	std::vector<std::string> getModelsNames();

	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;

	std::shared_ptr<MeshModel> popModel() const;
	std::vector<std::shared_ptr<MeshModel>> getModels() const;

	std::vector<Camera> GetCameras() const;
	void setModels(std::vector<std::shared_ptr<MeshModel>> models);
	std::shared_ptr<MeshModel> GetActiveModel();
	void updateModel(std::shared_ptr<MeshModel> m, int ind);

	
	// Add more methods as needed...
};