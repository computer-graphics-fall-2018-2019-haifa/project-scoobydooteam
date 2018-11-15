#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
protected:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 worldTransform= glm::mat4(1.0);
	glm::vec4 color;
	std::string modelName;
	glm::mat4x4 rotationVec=glm::mat4(1.0);
	glm::mat4x4 translationVec= glm::mat4(1.0);
	glm::mat4x4 scalingVec= glm::mat4(1.0);
	glm::vec3 center;



public:
	MeshModel();
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();
	MeshModel(MeshModel& model);

	void SetWorldTransformation(const glm::mat4x4& t);
	const glm::mat4x4& GetWorldTransformation() const;

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const std::string& GetModelName();
	const std::vector<glm::vec3>& getVertices();
	const std::vector<glm::vec3>& getNormals();
	const std::vector<Face>& getFaces();

	void setVertices(std::vector<glm::vec3> newVers);

	void setRotation(glm::mat4x4 m);
	void setTranslation(glm::mat4x4 m);
	void setScaling(glm::mat4x4 m);

	glm::mat4x4 getRotation();
	glm::mat4x4 getTranslation();
	glm::mat4x4 getScaling();

	glm::vec3 calcCenter();
	glm::vec3 getCenter();

};
