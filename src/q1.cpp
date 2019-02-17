// Display a cube, using glDrawElements

#include "common.h"
#include "Bezier.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const char *WINDOW_TITLE = "A2Q1";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint modelUniformLocation, viewUniformLocation, projectionUniformLocation;

Bezier *bez;

//----------------------------------------------------------------------------

// OpenGL initialization
void init()
{
   // Load shaders and use the resulting shader program
   GLuint program = InitShader("vshader.glsl", "fshader.glsl");
   glUseProgram(program);

   // set up vertex arrays
   GLuint vPosition = glGetAttribLocation(program, "vPosition");

   modelUniformLocation = glGetUniformLocation(program, "model");
   viewUniformLocation = glGetUniformLocation(program, "view");
   projectionUniformLocation = glGetUniformLocation(program, "projection");

   // setting default model transformation
   glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

   // setting default view transformation
   glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

   std::vector<glm::vec4> *cps = new std::vector<glm::vec4> {
	   glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
	   glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
	   glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
	   glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
   };

   bez = new Bezier(cps);
   bez->init(vPosition);

   glEnable(GL_DEPTH_TEST);
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   bez->display();

   glutSwapBuffers();
   glFinish();
}

//----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
       case 033: // Escape Key
       case 'q': case 'Q':
          exit(EXIT_SUCCESS);
          break;
    }
}

//----------------------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
       switch(button) {
          
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
