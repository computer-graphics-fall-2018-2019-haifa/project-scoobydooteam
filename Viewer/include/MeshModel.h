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
	glm::mat4x4 worldTransform;
	glm::vec4 color;
	std::string modelName;

public:
	MeshModel();
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();
	MeshModel(MeshModel& model);

	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const std::string& GetModelName();
	const std::vector<glm::vec3>& getVertices();
	const std::vector<glm::vec3>& getNormals();
	void setVertices(std::vector<glm::vec3> newVers);
	const std::vector<Face>& getFaces();
	void Scaling(double sx, double sy, double sz);
	void Rotation(double deg, int axis);
	void Translation(double tx, double ty, double tz);

};
