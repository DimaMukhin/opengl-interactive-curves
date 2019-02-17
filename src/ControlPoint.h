#pragma once

#include "common.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class ControlPoint
{
public:
	static std::vector<glm::vec4> *vertices;
	static Mesh *square;
	static bool initialized;

	ControlPoint(glm::vec4 location, GLuint modelUniformLocation);

	void init(GLuint vertexPositionAttribLocation);

	void display();

	glm::vec4 getLocation();

	void setLocation(glm::vec4 newLocation);

	~ControlPoint();

private:
	glm::vec4 location;
	GLuint VAO, VBO;
	GLuint modelUniformLocation;
};
