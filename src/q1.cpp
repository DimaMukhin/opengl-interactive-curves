/*
	Assignment 2 Question 1
	By Dima Mukhin
	#7773184
*/

#include "common.h"
#include "Bezier.h"
#include "CatmullRom.h"
#include "BSpline.h"
#include "ControlPoint.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>

const char *WINDOW_TITLE = "A2Q1";
const double FRAME_RATE_MS = 1000.0 / 60.0;
const float WIDTH = 640;
const float HEIGHT = 640;

// uniform locations
GLuint modelUniformLocation, viewUniformLocation, projectionUniformLocation;

std::vector<ControlPoint*> *cps;	// control points
Bezier *bez;						// bezier curve
CatmullRom *cat;					// catmul-rom curve
BSpline *bsp;						// b-spline curve

int currCurve = 0;					// 0 == bezier, 1 == catmull-rom, 2 == b-spline

//----------------------------------------------------------------------------

// OpenGL initialization
void init()
{
	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");

	// get all uniform variable locations
	modelUniformLocation = glGetUniformLocation(program, "model");
	viewUniformLocation = glGetUniformLocation(program, "view");
	projectionUniformLocation = glGetUniformLocation(program, "projection");

	// setting default model transformation
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	// setting default view transformation
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	// constructing default control points
	cps = new std::vector<ControlPoint*>{
		new ControlPoint(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), modelUniformLocation),
		new ControlPoint(glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f), modelUniformLocation),
		new ControlPoint(glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), modelUniformLocation),
		new ControlPoint(glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), modelUniformLocation),
	};

	// initializing all default control points
	for (int i = 0; i < cps->size(); i++) {
		(*cps)[i]->init(vPosition);
	}

	// constructing all curves
	bez = new Bezier(cps, vPosition);
	cat = new CatmullRom(cps, vPosition);
	bsp = new BSpline(cps, vPosition);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// displaying the right curve based on state (change state by pressing the space bar)
	if (currCurve == 0)
		bez->display();
	else if (currCurve == 1)
		cat->display();
	else
		bsp->display();

	for (int i = 0; i < cps->size(); i++) {
		(*cps)[i]->display();
	}

	glutSwapBuffers();
	glFinish();
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
	// press the space bar to switch between curve types
	switch (key) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case ' ':
		currCurve = (currCurve + 1) % 3;
		if (currCurve == 0) std::cout << "displaying Bezier curve" << std::endl;
		else if (currCurve == 1) std::cout << "displaying Catmull-Rom curve" << std::endl;
		else std::cout << "displaying uniform B-Spline curve" << std::endl;
		break;
	}
}

//----------------------------------------------------------------------------

ControlPoint *selectedCP = NULL;
void mouse(int button, int state, int x, int y)
{
	// handle mouse click
	// pick up control point if clicked on
	// put down control point after clicking on it
	// place a new control point otherwise
	if (state == GLUT_DOWN) {
		GLfloat tx = x / WIDTH;
		GLfloat ty = y / HEIGHT;
		GLfloat worldX = 2 * tx - 1;
		GLfloat worldY = -2 * ty + 1;

		if (selectedCP == NULL) {
			for (int i = 0; i < cps->size(); i++) {
				if ((*cps)[i]->pointInControlPoint(worldX, worldY)) {
					selectedCP = (*cps)[i];
					break;
				}
			}

			if (selectedCP == NULL) {
				cps->push_back(new ControlPoint(glm::vec4(worldX, worldY, 0.0f, 1.0f), modelUniformLocation));
				bez->generateBezierCurve();
				cat->generateCatmullRomCurve();
				bsp->generateBSplineCurve();
				std::cout << "placed a new control point at (" << worldX << ", " << worldY << ")" << std::endl;
			}
			else {
				std::cout << "picked up a control point, waiting for placement location input..." << std::endl;
			}
		}
		else {
			selectedCP->setLocation(glm::vec4(worldX, worldY, 0.0f, 1.0f));
			bez->generateBezierCurve();
			cat->generateCatmullRomCurve();
			bsp->generateBSplineCurve();
			selectedCP = NULL;
			std::cout << "moved the control point to (" << worldX << ", " << worldY << ")" << std::endl;
		}
	}
}

//----------------------------------------------------------------------------

void update(void)
{
}

//----------------------------------------------------------------------------

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
