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

void MeshModel::setVertices(std::vector<glm::vec3> newVers) {
	std::vector<glm::vec3> ver = this->getVertices();
	/*for (std::vector<glm::vec3>::iterator it = ver.begin(); it != ver.end(); it++)
	{
		this->vertices.erase(*it);
	}
	for (std::vector<glm::vec3>::iterator it = newVers.begin(); it != newVers.end(); it++)
	{
		this->vertices.push_back(*it);
	}*/


}

void MeshModel::Scaling(double sx, double sy, double sz) {
	std::vector<glm::vec3> newVers;
	glm::mat3x3 mat(sx, 0, 0, 0,sy,0,0,0,sz);
	std::vector<glm::vec3> ver = this->getVertices();
	int i = 0;
	for (std::vector<glm::vec3>::iterator it = ver.begin(); it != ver.end(); it++)
	{
		vertices[i++]=mat * (*it);
	}
}

void MeshModel::Rotation(double deg, int a) {

	std::vector<glm::vec3> newVers;
	std::vector<glm::vec3> ver = this->getVertices();
	int i = 0;
	glm::mat3x3 mat(0, 0, 0, 0, 0, 0, 0, 0, 0);
	if (a == 0)
	{
		if (deg > 0) {
			glm::mat3x3 mat1(1, 0, 0, 0, cos(deg), -sin(deg), 0, sin(deg), cos(deg));
			mat = mat1;
		}
		else {
			glm::mat3x3 mat1(1, 0, 0, 0, cos(deg), sin(deg), 0, -sin(deg), cos(deg));
			mat = mat1;
		}
	}
	else if (a == 1) {
		if (deg > 0) {
			glm::mat3x3 mat2(cos(deg), 0, sin(deg), 0, 1, 0, -sin(deg), 0, cos(deg));
			mat = mat2;
		}
		else {
			glm::mat3x3 mat2(cos(deg), 0, -sin(deg), 0, 1, 0, sin(deg), 0, cos(deg));
			mat = mat2;
		}
	}
	else if (a == 2)
	{
		if (deg > 0){
			glm::mat3x3 mat3(cos(deg), -sin(deg), 0, sin(deg), cos(deg), 0, 0, 1, 1);
			mat = mat3;
		}
		else {
			glm::mat3x3 mat3(cos(deg), sin(deg), 0, -sin(deg), cos(deg), 0, 0, 1, 1);
			mat = mat3;
		}
	}
	for (std::vector<glm::vec3>::iterator it = ver.begin(); it != ver.end(); it++)
	{
		vertices[i++] = mat * (*it);
	}
}

/*TODO: the mat mul does not work correctly!*/
void MeshModel::Translation(double tx, double ty, double tz) {
	//std::vector<glm::vec3> newVers;
	
	glm::vec4 m0(1, 0, 0, tx);
	glm::vec4 m1(0, 1, 0, ty);
	glm::vec4 m2(0, 0, 1, tz);
	//glm::mat4x4 mat(&m0,&m1,&m2,(0,0,0,1));


	//std::vector<glm::vec3> ver = this->getVertices();
	int i = 0;
	for (std::vector<glm::vec3>::iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		//vertices[i] = mat * (*it);
		vertices[i].x = vertices[i].x / vertices[i].z;
		vertices[i].y = vertices[i].y / vertices[i].z;
		vertices[i].z = 1;
		
		i++;
	}
}