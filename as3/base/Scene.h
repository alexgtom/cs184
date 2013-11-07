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

#include "BezierPatch.h"
#include "Parser.h"

#define SUBDIVISION_ADAPTIVE 0
#define SUBDIVISION_UNIFORM 1
#define DEFAULT_SUBDIVISION_PARAMETER 0.1

using namespace std;

class Scene {
  public:
    int width, height; // width and height of the window
    string inputFile;
    float subdivisionParameter;
    int subdivisionType;
    vector<BezierPatch> patch_list;

    Scene() {
      width = 400;
      height = 300;
      subdivisionType = SUBDIVISION_UNIFORM;
      subdivisionParameter = DEFAULT_SUBDIVISION_PARAMETER;
    };
    
    // parse arguements from command line and set stuff
    void parseArgs(int argc, char *argv[]) {
      if (argc != 3 && argc != 4) {
        cerr << "Invalid arguments" << endl;
        cerr << "USAGE: ./main inputfile.bez 0.1 -a" << endl;
        exit(1);
      }

      inputFile = argv[1];
      subdivisionParameter = atof(argv[2]);
      
      if (argc == 4) {
        if (strcmp(argv[3], "-a") == 0)
          subdivisionType = SUBDIVISION_ADAPTIVE;
        else
          subdivisionType = SUBDIVISION_UNIFORM;
      }
    }
    
    // create everything for the scene
    void create(int argc, char *argv[]) {
      // parse arguements from command line
      parseArgs(argc, argv);
      
      // parse input file and return a patch list
      Parser parser;
      patch_list = parser.readFile(inputFile, subdivisionParameter);
    }

    // render the scene in the GLUT loop
    void render() {
      for(int i = 0; i < patch_list.size(); i++) {
        patch_list[i].render();
      }
    }

    // keyboard controls for the scene from the keyboard
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
