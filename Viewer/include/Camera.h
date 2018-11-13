#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"

/*
 * Camera class. This class takes care of all the camera transformations and manipulations.
 *
 * Implementation suggestion:
 * --------------------------
 * Make the Camera class be a subclass of MeshModel, so you can easily and elegantly render 
 * the cameras you have added to the scene.
 */
class Camera : public MeshModel
{
private:
	glm::mat4x4 viewTransformation;
	glm::mat4x4 projectionTransformation;
	float zoom;

public:
	Camera();
	Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up);
	Camera(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
		const std::string& modelName, const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up);
	Camera(MeshModel& m);
	Camera(Camera& c);
	Camera(const Camera& c);
	~Camera();

	glm::mat4x4 getViewTransformation();
	void setViewTransformation(const glm::mat4x4 mat);
	glm::mat4x4 getProjectionTransformation();
	void setProjectionTransformation(const glm::mat4x4 mat);


	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

	void SetOrthographicProjection(
		const float height,
		const float aspectRatio,
		const float near,
		const float far);

	void SetPerspectiveProjection(
		const float fovy,
		const float aspect,
		const float near,
		const float far);

	void SetZoom(const float zoom);

	



	// Add more methods/functionality as needed...
};
