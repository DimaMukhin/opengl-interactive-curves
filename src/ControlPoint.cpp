#include "ControlPoint.h"

// square vertices
std::vector<glm::vec4>* ControlPoint::vertices = new std::vector<glm::vec4>{
	glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
	glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
	glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),

	glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
	glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
	glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
};

// square mesh
Mesh* ControlPoint::square = new Mesh(vertices);

bool ControlPoint::initialized = false;

ControlPoint::ControlPoint(glm::vec4 location, GLuint modelUniformLocation)
{
	this->location = location;
	this->modelUniformLocation = modelUniformLocation;
}

// initialize the control point
void ControlPoint::init(GLuint vertexPositionAttribLocation)
{
	if (!initialized) {
		square->init(vertexPositionAttribLocation);
		initialized = true;
	}
}

// display the control point
void ControlPoint::display()
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(location));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	square->display();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
}

// get the world location of the control point
glm::vec4 ControlPoint::getLocation()
{
	return location;
}

// set the world location of the control point
void ControlPoint::setLocation(glm::vec4 newLocation)
{
	location = newLocation;
}

// check if a world (x, y) point is inside the control point (point in square)
bool ControlPoint::pointInControlPoint(GLfloat x, GLfloat y)
{
	return x <= location.x + 0.03 && x >= location.x - 0.03
		&& y <= location.y + 0.03 && y >= location.y - 0.03;
}

ControlPoint::~ControlPoint()
{
}
