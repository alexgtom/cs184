#ifndef SCENE_H_
#define SCENE_H_

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


class Scene {
  public:
    int width, height; // width and height of the window

    Scene() {
      width = 400;
      height = 300;
    };
    
    static void keyboard(unsigned char key, int x, int y)
    {
      if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        switch(key) {
          // translations
          case GLUT_KEY_UP:
            break;
          case GLUT_KEY_DOWN:
            break;
          case GLUT_KEY_LEFT:
            break;
          case GLUT_KEY_RIGHT:
            break;
        }
      } else {
        switch(key) {
          // toggle between flat and smooth shading
          case 's':
            break;
          // toggle between filled and wireframe mode
          case 'w':
            break;

          // rotations
          case GLUT_KEY_UP:
            break;
          case GLUT_KEY_DOWN:
            break;
          case GLUT_KEY_LEFT:
            break;
          case GLUT_KEY_RIGHT:
            break;

          // zoom
          case '+':
            break;
          case '-':
            break;

          // quit
          case 'q':
          case 27:
            exit(0);
            break;
        }
      }

      glutPostRedisplay();
    }
};

#endif
