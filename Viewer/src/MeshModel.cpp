#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel(): modelName(modelName), worldTransform(glm::mat4x4(1))
{

}

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1))
{
	this->faces = faces;
	this->vertices = vertices;
	this->normals = normals;
	this->center=calcCenter();	
}

MeshModel::MeshModel(MeshModel& model)
{
	this->faces = model.getFaces();
	this->vertices = model.getVertices();
	this->normals = model.getNormals();
	this->modelName = model.GetModelName();
	this->center = model.getCenter();
}

MeshModel::~MeshModel()
{
	/*this->faces.clear();
	this->vertices.clear();
	this->normals.clear();*/
}

glm::vec3 MeshModel::calcCenter() {
	float len = faces.size();
	float face = 3.0;
	glm::vec3 c(0, 0, 0);
	for (std::vector<Face>::iterator it = this->faces.begin(); it != this->faces.end(); it++)
	{
		glm::vec3 faceCenter(0.0, 0.0, 0.0);
		for (int i = 0; i < 3; i++)
			faceCenter += this->vertices.at(it->GetVertexIndex(i) - 1);
		faceCenter = faceCenter / face;
		c += faceCenter;
	}
	c = c / len;
	return c;
}

void MeshModel::SetWorldTransformation(const glm::mat4x4& t)
{
	this->worldTransform = t* this->worldTransform;
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

void MeshModel::setVertices(std::vector<glm::vec3> newVers) {
	std::vector<glm::vec3> ver = this->getVertices();
		this->vertices.clear();
	
	for (std::vector<glm::vec3>::iterator it = newVers.begin(); it != newVers.end(); it++)
	{
		this->vertices.push_back(*it);
	}
}

void MeshModel::setRotation(glm::mat4x4 m) {
	this->worldTransform = m * this->worldTransform;
}

void MeshModel::setTranslation(glm::mat4x4 m) {
	this->worldTransform = m * this->worldTransform;
	this->center.x += m[3][0];
	this->center.y += m[3][1];
	this->center.z += m[3][2];

}
void MeshModel::setScaling(glm::mat4x4 m) {
	this->worldTransform = m * this->worldTransform;
}

glm::mat4x4 MeshModel::getRotation() {
	return this->rotationVec;
}
glm::mat4x4 MeshModel::getTranslation() {
	return this->translationVec;
}
glm::mat4x4 MeshModel::getScaling() {
	return this->scalingVec;
}

glm::vec3 MeshModel::getCenter() {
	return this->center;
}
