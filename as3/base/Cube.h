#ifndef CUBE_H_
#define CUBE_H_

#include <glm/glm.hpp>
#include <vector>

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

#include "BezierPatch.h"

class Cube : public BezierPatch {
  public:
    Cube() {}
    Cube(vector<vec3> points, float subdivisionParameter) : BezierPatch(points, subdivisionParameter) {
    }
    void render(void) {
      // White side - BACK
      glBegin(GL_POLYGON);
      glColor3f(   1.0,  1.0, 1.0 );
      glVertex3f(  0.5, -0.5, 0.5 );
      glVertex3f(  0.5,  0.5, 0.5 );
      glVertex3f( -0.5,  0.5, 0.5 );
      glVertex3f( -0.5, -0.5, 0.5 );
      glEnd();

      // Purple side - RIGHT
      glBegin(GL_POLYGON);
      glColor3f(  1.0,  0.0,  1.0 );
      glVertex3f( 0.5, -0.5, -0.5 );
      glVertex3f( 0.5,  0.5, -0.5 );
      glVertex3f( 0.5,  0.5,  0.5 );
      glVertex3f( 0.5, -0.5,  0.5 );
      glEnd();

      // Green side - LEFT
      glBegin(GL_POLYGON);
      glColor3f(   0.0,  1.0,  0.0 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
      glEnd();

      // Blue side - TOP
      glBegin(GL_POLYGON);
      glColor3f(   0.0,  0.0,  1.0 );
      glVertex3f(  0.5,  0.5,  0.5 );
      glVertex3f(  0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glEnd();

      // Red side - BOTTOM
      glBegin(GL_POLYGON);
      glColor3f(   1.0,  0.0,  0.0 );
      glVertex3f(  0.5, -0.5, -0.5 );
      glVertex3f(  0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
      glEnd();
    }
};

#endif
