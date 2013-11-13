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
#include "Cube.h"
#include "Parser.h"
#include "Subdivision.h"

#define ROTATE_STEP_SIZE 5.0f
#define ZOOM_STEP_SIZE 0.1f
#define TRANSLATE_STEP_SIZE 0.1f

#define WIREFRAME 0
#define FILLED 1

#define FLAT 0
#define SMOOTH 1

using namespace std;

class Scene {
  public:
    int width, height; // width and height of the window
    string inputFile;
    float subdivisionParameter;
    int subdivisionType;
    vector<BezierPatch*> patch_list;
    static float rotate_x, rotate_y;
    static float translate_x, translate_y;
    static float scale;
    static int render_mode;
    static int shading_mode;

    Scene() {
      width = 400;
      height = 300;
      subdivisionType = SUBDIVISION_UNIFORM;
      subdivisionParameter = DEFAULT_SUBDIVISION_PARAMETER;
      rotate_x = rotate_y = 0;
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
      patch_list = parser.readFile(inputFile, subdivisionParameter, subdivisionType);
    }

    // render the scene in the GLUT loop
    void render() {
      //Cube c;
      //c.render();
      for(int i = 0; i < patch_list.size(); i++) {
        if (render_mode == WIREFRAME)
          patch_list[i]->render_wireframe();
        else
          patch_list[i]->render_filled();
      }

      // lighting
      createLight();
    }

    void createLight() {
      GLfloat mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
      GLfloat mat_shininess[] = { 10.0 };
      GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
      glClearColor(0.0, 0.0, 0.0, 0.0);

      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glEnable(GL_COLOR_MATERIAL);
    }

    // keyboard controls for the scene from the keyboard
    static void keyboard(int key, int x, int y)
    {
      if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        switch(key) {
          // translations
          case GLUT_KEY_UP:
            translate_y += TRANSLATE_STEP_SIZE;
            break;
          case GLUT_KEY_DOWN:
            translate_y -= TRANSLATE_STEP_SIZE;
            break;
          case GLUT_KEY_LEFT:
            translate_x += TRANSLATE_STEP_SIZE;
            break;
          case GLUT_KEY_RIGHT:
            translate_x -= TRANSLATE_STEP_SIZE;
            break;

          // zoom in 
          case '+':
            scale += ZOOM_STEP_SIZE;
            break;
        }
      } else {
        switch(key) {
          // toggle between flat and smooth shading
          case 's':
            if (shading_mode == FLAT) {
              glEnable(GL_FLAT);
              glShadeModel(GL_FLAT);
              shading_mode = SMOOTH;
            } else {
              glEnable(GL_SMOOTH);
              glShadeModel(GL_SMOOTH);
              shading_mode = FLAT;
            }
            break;
          // toggle between filled and wireframe mode
          case 'w':
            if (render_mode == WIREFRAME)
              render_mode = FILLED;
            else
              render_mode = WIREFRAME;
            break;

          // rotations
          case GLUT_KEY_UP:
            rotate_x += ROTATE_STEP_SIZE;
            break;
          case GLUT_KEY_DOWN:
            rotate_x -= ROTATE_STEP_SIZE;
            break;
          case GLUT_KEY_LEFT:
            rotate_y -= ROTATE_STEP_SIZE;
            break;
          case GLUT_KEY_RIGHT:
            rotate_y += ROTATE_STEP_SIZE;
            break;

          // zoom out
          case '-':
            scale -= ZOOM_STEP_SIZE;
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

float Scene::rotate_x = 0.0f;
float Scene::rotate_y = 0.0f;
float Scene::translate_x = 0.0f;
float Scene::translate_y = 0.0f;
float Scene::scale = 1.0f;
int Scene::render_mode = FILLED;
int Scene::shading_mode = FLAT;

#endif
