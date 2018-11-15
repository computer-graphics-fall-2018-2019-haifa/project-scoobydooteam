#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
}
std::vector<std::string> Scene::getModelsNames()
{
	std::vector<std::string> names;
	for (std::vector<std::shared_ptr<MeshModel>>::iterator itr = models.begin(); itr != models.end(); itr++)
	{
		names.push_back((*itr)->GetModelName());
	}
	return names;
}

std::shared_ptr<MeshModel> Scene::popModel() const
{
	if(!models.empty())
		return models.front();
	return NULL;
}

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::AddCamera(const Camera& camera)
{
	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}
std::shared_ptr<MeshModel> Scene::GetActiveModel()
{
	return this->models[this->activeModelIndex];
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	if (models.size() != 0)
		return activeModelIndex;
	return -1;
}

std::vector<std::shared_ptr<MeshModel>> Scene::getModels() const {
	return this->models;
}

std::vector<Camera> Scene::GetCameras() const {
	return this->cameras;
}

void Scene::setModels(std::vector<std::shared_ptr<MeshModel>> models) {
	std::vector<std::shared_ptr<MeshModel>> ver = this->getModels();
	this->models.clear();

	for (std::vector<std::shared_ptr<MeshModel>>::iterator it = models.begin(); it != models.end(); it++)
	{
		this->models.push_back(*it);
	}
}

void Scene::updateModel(std::shared_ptr<MeshModel> m, int ind) {
	this->models[ind] = m;
}