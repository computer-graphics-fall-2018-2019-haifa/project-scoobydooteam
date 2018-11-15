#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Camera::Camera()
{

}

Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0), MeshModel()
{
	SetCameraLookAt(eye, at, up);
}

Camera::Camera(MeshModel& m)
{
	MeshModel(m.getFaces(), m.getVertices(), m.getNormals(), m.GetModelName());
}

Camera::Camera(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
	const std::string& modelName, const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up):
	MeshModel(faces,vertices,normals,modelName)
{
	SetCameraLookAt(eye, at, up);
}
Camera::Camera(Camera& c) {
	MeshModel(c.getFaces(), c.getVertices(), c.getNormals(), c.GetModelName());
	this->viewTransformation = c.getViewTransformation();
	this->projectionTransformation = c.getProjectionTransformation();
}

Camera::Camera(const Camera& c) {
}

//Camera::Camera(MeshModel m,const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	//zoom(1.0)
//{
	//MeshModel m1=MeshModel(m);
	//SetCameraLookAt(eye, at, up);
	//return const_cast<Camera>(m1);
//}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	glm::vec4 z = glm::vec4(normalize(eye - at),0);
	glm::vec4 x = glm::vec4(normalize(cross(up, normalize(eye - at))),0);
	glm::vec4 y = glm::vec4(normalize(cross(normalize(eye - at), normalize(cross(up, normalize(eye - at))))),0);
	glm::vec4 t = glm::vec4(0.0, 0.0,0.0, 1.0);
	glm::mat4x4 mat(x, y, z, t);
	mat = glm::transpose(mat);
	//this->setViewTransformation(mat*c);
}

void Camera::SetOrthographicProjection(const float height,const float aspectRatio,const float near,const float far)
{
	float top = height;
	float bottom = -top;
	float right = top * aspectRatio;
	float left = -right;
	glm::vec4 m0(2 / (right - left), 0, 0, -(right + left) / (right - left));
	glm::vec4 m1(0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom));
	glm::vec4 m2(0, 0, -2 / (far - near), -(far + near) / (far - near));
	glm::vec4 m3(0, 0, 0, 1.0);
	glm::mat4x4 mat(m0, m1, m2, m3);
	this->setProjectionTransformation(mat);

}

/* fovy:The field of view */
void Camera::SetPerspectiveProjection(const float fovy,const float aspectRatio,const float near,const float far)
{
	float top=near*tan(fovy);
	float right=top*aspectRatio;
	glm::vec4 m0(near / right, 0, 0, 0);
	glm::vec4 m1(0, near / top, 0, 0);
	glm::vec4 m2(0,0,-(far+near) / (far-near), (-2*far*near)/(far-near));
	glm::vec4 m3(0,0,-1,0);
	glm::mat4x4 mat(m0, m1, m2, m3);
	this->setProjectionTransformation(mat);
	this->SetCameraLookAt(glm::vec3(center.x, center.y, center.z), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
	
	//this->viewTransformation=
}

void Camera::SetZoom(const float zoom)
{

}

glm::mat4x4 Camera::getViewTransformation() {
	return this->viewTransformation;
}

void Camera::setViewTransformation(const glm::mat4x4 t) {
	this->viewTransformation = t*this->viewTransformation;
}

glm::mat4x4 Camera::getProjectionTransformation() {
	return this->projectionTransformation;
}
void Camera::setProjectionTransformation(const glm::mat4x4 mat) {
	this->projectionTransformation = mat;
}