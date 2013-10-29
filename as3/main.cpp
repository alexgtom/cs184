
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#include "base/Scene.h"

using namespace std;

Scene scene;

//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT);	  // clear the color buffer

  glMatrixMode(GL_MODELVIEW);			// indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"

  // Start drawing stuff here

  glFlush();
  glutSwapBuffers();					    // swap buffers (we earlier set double buffer)
}

int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  //The size and position of the window
  glutInitWindowSize(scene.width, scene.height);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutKeyboardFunc(scene.keyboard);

  glutMainLoop();						// 999  //TODO: this is supposed to be infinityloop that will keep drawing and resizing
  // and whatever else

  return 0;
}
