#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1))
{
	this->faces = faces;
	this->vertices = vertices;
	this->normals = normals;
}

MeshModel::MeshModel(MeshModel& model)
{
	this->faces = model.getFaces();
	this->vertices = model.getVertices();
	this->normals = model.getNormals();
	this->modelName = modelName;
}

MeshModel::~MeshModel()
{
	/*this->faces.clear();
	this->vertices.clear();
	this->normals.clear();*/
}

void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

const glm::mat4x4& MeshModel::GetWorldTransformation() const
{
	return worldTransform;
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec4& MeshModel::GetColor() const
{
	return color;
}

const std::string& MeshModel::GetModelName()
{
	return modelName;
}

const std::vector<glm::vec3>& MeshModel::getVertices() 
{
	return vertices;
}

const std::vector<glm::vec3>& MeshModel::getNormals()
{
	return normals;
}

const std::vector<Face>& MeshModel::getFaces()
{
	return faces;
}