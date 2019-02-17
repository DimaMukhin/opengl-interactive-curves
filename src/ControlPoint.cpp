#include "ControlPoint.h"

std::vector<glm::vec4>* ControlPoint::vertices = new std::vector<glm::vec4> {
	glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
	glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
	glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),

	glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
	glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
	glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
};

Mesh* ControlPoint::square = new Mesh(vertices);

bool ControlPoint::initialized = false;

ControlPoint::ControlPoint(glm::vec4 location, GLuint modelUniformLocation)
{
	this->location = location;
	this->modelUniformLocation = modelUniformLocation;
}

void ControlPoint::init(GLuint vertexPositionAttribLocation)
{
	if (!initialized) {
		square->init(vertexPositionAttribLocation);
		initialized = true;
	}
}

void ControlPoint::display()
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(location));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	square->display();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
}

glm::vec4 ControlPoint::getLocation()
{
	return location;
}

void ControlPoint::setLocation(glm::vec4 newLocation)
{
	location = newLocation;
}

ControlPoint::~ControlPoint()
{
}
