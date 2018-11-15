#include "Utils.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

glm::vec3 Utils::Vec3fFromStream(std::istream& issLine)
{
	float x, y, z;
	issLine >> x >> std::ws >> y >> std::ws >> z;
	return glm::vec3(x, y, z);
}

glm::vec2 Utils::Vec2fFromStream(std::istream& issLine)
{
	float x, y;
	issLine >> x >> std::ws >> y;
	return glm::vec2(x, y);
}

MeshModel Utils::LoadMeshModel(const std::string& filePath)
{
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::ifstream ifile(filePath.c_str());

	// while not end of file
	while (!ifile.eof())
	{
		// get line
		std::string curLine;
		std::getline(ifile, curLine);

		// read the type of the line
		std::istringstream issLine(curLine);
		std::string lineType;

		issLine >> std::ws >> lineType;

		// based on the type parse data
		if (lineType == "v")
		{
			vertices.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vn")
		{
			normals.push_back(Utils::Vec3fFromStream(issLine));
		}
		else if (lineType == "vt")
		{
			// Texture coordinates
		}
		else if (lineType == "f")
		{
			faces.push_back(Face(issLine));
		}
		else if (lineType == "#" || lineType == "")
		{
			// comment / empty line
		}
		else
		{
			std::cout << "Found unknown line Type \"" << lineType << "\"";
		}
	}

	return MeshModel(faces, vertices, normals, Utils::GetFileName(filePath));
}

std::string Utils::GetFileName(const std::string& filePath)
{
	if (filePath.empty()) {
		return {};
	}

	auto len = filePath.length();
	auto index = filePath.find_last_of("/\\");

	if (index == std::string::npos) {
		return filePath;
	}

	if (index + 1 >= len) {

		len--;
		index = filePath.substr(0, len).find_last_of("/\\");

		if (len == 0) {
			return filePath;
		}

		if (index == 0) {
			return filePath.substr(1, len - 1);
		}

		if (index == std::string::npos) {
			return filePath.substr(0, len);
		}

		return filePath.substr(index + 1, len - index - 1);
	}

	return filePath.substr(index + 1, len - index);
}

glm::mat4x4  Utils::Scaling(glm::vec3 vec) {

	glm::mat4x4 trans = glm::mat4(1.0);

	if(vec.x != 0) trans[0][0] = vec.x;
	if (vec.y != 0) trans[1][1] = vec.y;
	if (vec.z != 0) trans[2][2] = vec.z;
	return trans;
}

glm::mat4x4   Utils::Rotation(glm::vec3 vec) {

	if (vec.x != 0)
	{
		if (vec.x > 0) {
			glm::vec4 m0(1, 0, 0, 0);
			glm::vec4 m1(0, cos(vec.x), -sin(vec.x), 0);
			glm::vec4 m2(0, sin(vec.x), cos(vec.x), 0);
			glm::vec4 m3(0, 0, 0, 1);
			glm::mat4x4 mat(m0, m1, m2, m3);
			return mat;
		}
		else {
			glm::vec4 m0(1, 0, 0, 0);
			glm::vec4 m1(0, cos(vec.x), sin(vec.x), 0);
			glm::vec4 m2(0, -sin(vec.x), cos(vec.x), 0);
			glm::vec4 m3(0, 0, 0, 1);
			glm::mat4x4 mat(m0, m1, m2, m3);
			return mat;
		}
	}
	else if (vec.y != 0) {
		if (vec.y > 0) {
			glm::vec4 m0(cos(vec.y), 0, sin(vec.y), 0);
			glm::vec4 m1(0, 1, 0, 0);
			glm::vec4 m2(-sin(vec.y), 0, cos(vec.y), 0);
			glm::vec4 m3(0, 0, 0, 1);
			glm::mat4x4 mat(m0, m1, m2, m3);
			return mat;
		}
		else {
			glm::vec4 m0(cos(vec.y), 0, -sin(vec.y), 0);
			glm::vec4 m1(0, 1, 0, 0);
			glm::vec4 m2(sin(vec.y), 0, cos(vec.y), 0);
			glm::vec4 m3(0, 0, 0, 1);
			glm::mat4x4 mat(m0, m1, m2, m3);
			return mat;
		}
	}
	else if (vec.z != 0)
	{
		if (vec.z > 0) {
			glm::vec4 m0(cos(vec.z), -sin(vec.z), 0, 0);
			glm::vec4 m1(sin(vec.z), cos(vec.z), 0, 0);
			glm::vec4 m2(0, 0, 1, 0);
			glm::vec4 m3(0, 0, 0, 1);
			glm::mat4x4 mat(m0, m1, m2, m3);
			return mat;
		}
		else {
			glm::vec4 m0(cos(vec.z), sin(vec.z), 0, 0);
			glm::vec4 m1(-sin(vec.z), cos(vec.z), 0, 0);
			glm::vec4 m2(0, 0, 1, 0);
			glm::vec4 m3(0, 0, 0, 1);
			glm::mat4x4 mat(m0, m1, m2, m3);
			return mat;
		}
	}
	glm::vec4 m0(1, 0, 0, 0);
	glm::vec4 m1(0, 1, 0, 0);
	glm::vec4 m2(0,0, 1, 0);
	glm::vec4 m3(0, 0, 0, 1);
	glm::mat4x4 mat(m0, m1, m2, m3);
	return mat;
}

/*TODO: the mat mul does not work correctly!*/
glm::mat4x4  Utils::Translation(glm::vec3 t) {
	glm::mat4x4 trans = glm::mat4(1.0);

	trans[3][0] = t.x;
	trans[3][1] = t.y;
	trans[3][2] = t.z;
	return trans;
}