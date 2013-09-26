
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

#include "Vec3.h"


#define PI 3.14159265  // Should be used from mathlib
#define DEBUG_ARGS false
inline float sqr(float x) { return x*x; }

using namespace std;


//****************************************************
// Arguments
//****************************************************

float ka_r = 0.0f;
float ka_g = 0.0f;
float ka_b = 0.0f;

float kd_r = 0.0f;
float kd_g = 0.0f;
float kd_b = 0.0f;

float ks_r = 0.0f;
float ks_g = 0.0f;
float ks_b = 0.0f;

float sp_v = 0.0f;

// there can be multuple light sources
vector<Vec3> pl;

vector<float> pl_r;
vector<float> pl_g;
vector<float> pl_b;

vector<Vec3> dl;

vector<float> dl_r;
vector<float> dl_g;
vector<float> dl_b;

//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
  public:
    int w, h; // width and height
};

/* 
 * Math Operations
 */

//TODO: print_vector does not work for new vectors yet
void print_vector(const vector<float>& v) {
  for(int i = 0; i < v.size(); i++) {
    cout << v[i] << endl;
  }
}

float max3(float a1, float a2, float a3) {
  return max(max(a1, a2), a3);
}

float max_num_from_vector(vector<float>& v) {
  float m = 0.0f;
  for (int i = 0; i < v.size(); i++) {
    m = max(v[i], m);
  }
  return m;
}

float magnitude(float x, float y, float z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void normalize_vector(float& x, float& y, float& z) {
  float m = magnitude(x, y, z);
  x = x / m;
  y = y / m;
  z = z / m;
}

class PixelOps;

class PixelOps {
  public:
    // coordinates on sphere
    Vec3 v;

    // r, g, b, are values between [0.0f, 1.9f]
    float r, g, b;

    PixelOps(Vec3 v) : v(v) {
      r = g = b = 0.0f;
    }

    /* 
     * Ambient Component
     */
    PixelOps& ambientComponent(float r, float g, float b) {
      // add ambient component
      this->r += ka_r * r;
      this->g += ka_g * g;
      this->b += ka_b * b;

      return *this;
    }

    /*
     * Diffuse Shading
     *
     * x, y, z is the direction of the light
     */
    PixelOps& diffuseComponent(Vec3 light_direction, float r, float g, float b) {
      // light vector
      light_direction = light_direction.norm();

      // normal vector
      Vec3 normal = this->v.norm();
    
      // max(0, n.v)
      float m = max(0.0f, light_direction.dot(normal));
      
      // add diffuse component
      this->r += m * kd_r * r;
      this->g += m * kd_g * g;
      this->b += m * kd_b * b;
      
      return *this;
    }

    /*
     * Specular Component
     */
    PixelOps& specularComponent(Vec3 light_direction, float r, float g, float b) {
      // light vector
      light_direction = light_direction.norm();

      // normal vector
      Vec3 normal = this->v.norm();

      // reflected direction
      Vec3 reflected_direction = -light_direction + (2 * light_direction.dot(normal) * normal);
      reflected_direction = reflected_direction.norm();

      // viewer direction
      Vec3 viewer_direction = Vec3(0, 0, 1); //normalized

      // max term
      float m = max(0.0f, reflected_direction.dot(viewer_direction));

      // add specular component
      this->r += pow(m, sp_v) * ks_r * r;
      this->g += pow(m, sp_v) * ks_g * g;
      this->b += pow(m, sp_v) * ks_b * b;

      return *this;
    }

    /* Example
     * -------
     *
     * Function Chaining: 
     *
     * PixelOps op;
     * op.opacity(0.4f).opacity(0.2f)
     */
    PixelOps& opacity(float o) {
      r = r * o;
      g = g * o;
      b = b * o;

      return *this;
    }

    /*
     * Calculate everything
     */
    void renderDirectionalLight(Vec3 light_direction, float r, float g, float b) {
      ambientComponent(r, g, b);
      diffuseComponent(-light_direction, r, g, b);
      specularComponent(-light_direction, r, g, b);
    }

    void renderPointLight(Vec3 light_location, float r, float g, float b) {
      ambientComponent(r, g, b);

      // make light shine to point
      diffuseComponent(light_location - this->v, r, g, b);
      specularComponent(light_location - this->v, r, g, b);
    }
};

//****************************************************
// Global Variables
//****************************************************
Viewport	viewport;




//****************************************************
// Simple init function
//****************************************************
void initScene(){

  // Nothing to do here for this simple example.

}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);

}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
  glColor3f(r, g, b);
  glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
  // centers 
  // Note: Need to check for gap
  // bug on inst machines.
}

//****************************************************
// Draw a filled circle.  
//****************************************************


void circle(float centerX, float centerY, float radius) {
  // Draw inner circle
  glBegin(GL_POINTS);

  // We could eliminate wasted work by only looping over the pixels
  // inside the sphere's radius.  But the example is more clear this
  // way.  In general drawing an object by loopig over the whole
  // screen is wasteful.

  int i,j;  // Pixel indices

  int minI = max(0,(int)floor(centerX-radius));
  int maxI = min(viewport.w-1,(int)ceil(centerX+radius));

  int minJ = max(0,(int)floor(centerY-radius));
  int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));



  for (i=0;i<viewport.w;i++) {
    for (j=0;j<viewport.h;j++) {

      // Location of the center of pixel relative to center of sphere
      float x = (i+0.5-centerX);
      float y = (j+0.5-centerY);

      float dist = sqrt(sqr(x) + sqr(y));

      if (dist<=radius) {

        // This is the front-facing Z coordinate
        float z = sqrt(radius*radius-dist*dist);

        // normalize x, y, and z into coordinate system
        PixelOps po(Vec3(x / radius, y / radius, z / radius));

        // finds the maximum color value out of all the lights
        float max_color_value = max(max3(max_num_from_vector(pl_r),
                                         max_num_from_vector(pl_g),
                                         max_num_from_vector(pl_b)),
                                    max3(max_num_from_vector(dl_r),
                                         max_num_from_vector(dl_g),
                                         max_num_from_vector(dl_b)));

        // iterate through each point light
        for(int a = 0; a < pl.size(); a++) {
          // normalize each light intensity to between [0.0, 1.0]
          float r = pl_r[a] / max_color_value;
          float g = pl_g[a] / max_color_value;
          float b = pl_b[a] / max_color_value;

          po.renderPointLight(pl[a], r, g, b);
        }

        // iterate through each directional light
        for(int a = 0; a < dl.size(); a++) {
          // normalize each light intensity to between [0.0, 1.0]
          float r = dl_r[a] / max_color_value;
          float g = dl_g[a] / max_color_value;
          float b = dl_b[a] / max_color_value;

          po.renderDirectionalLight(dl[a], r, g, b);
        }

        setPixel(i, j, po.r, po.g, po.b);

        // This is amusing, but it assumes negative color values are treated reasonably.
        // setPixel(i,j, x/radius, y/radius, z/radius );
      }


    }
  }


  glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

  glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"


  // Start drawing
  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glFlush();
  glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}



//****************************************************
// the usual stuff, nothing exciting here
//****************************************************

void parseArgs(int argc, char *argv[]) {
  if (DEBUG_ARGS) {
    cout << "---[ DEBUG ARGS ] -------------------"  << endl;
    for(int i = 0; i < argc; i++) {
      cout << i << ": " << argv[i] << endl;
    }
  }

  for(int i = 1; i < argc;) {
    char *option = argv[i];

    if (strcmp(option, "-ka") == 0) {
      ka_r = atof(argv[i + 1]);
      ka_g = atof(argv[i + 2]);
      ka_b = atof(argv[i + 3]);
      i += 4;
    } else if (strcmp(option, "-kd") == 0) {
      kd_r = atof(argv[i + 1]);
      kd_g = atof(argv[i + 2]);
      kd_b = atof(argv[i + 3]);
      i += 4;
    } else if (strcmp(option, "-ks") == 0) {
      ks_r = atof(argv[i + 1]);
      ks_g = atof(argv[i + 2]);
      ks_b = atof(argv[i + 3]);
      i += 4;
    } else if (strcmp(option, "-sp") == 0) {
      sp_v = atof(argv[i + 1]);
      i += 2;
    } else if (strcmp(option, "-pl") == 0) {
      pl.push_back(Vec3(atof(argv[i + 1]), 
                        atof(argv[i + 2]), 
                        atof(argv[i + 3])));
      pl_r.push_back(atof(argv[i + 4]));
      pl_g.push_back(atof(argv[i + 5]));
      pl_b.push_back(atof(argv[i + 6]));
      i += 7;
    } else if (strcmp(option, "-dl") == 0) {
      dl.push_back(Vec3(atof(argv[i + 1]), 
                        atof(argv[i + 2]), 
                        atof(argv[i + 3])));
      dl_r.push_back(atof(argv[i + 4]));
      dl_g.push_back(atof(argv[i + 5]));
      dl_b.push_back(atof(argv[i + 6]));
      i += 7;
    } else {
      cerr << "Invalid argument: " << option << endl;
      exit(1);
    }
  }

  if (DEBUG_ARGS) {
    cout << "---[ ARGS PARSED ] -------------------" << endl;
    cout << "ka_r" << ": " << ka_r << endl;
    cout << "ka_g" << ": " << ka_g << endl;
    cout << "ka_b" << ": " << ka_b << endl;
    cout << "kd_r" << ": " << kd_r << endl;
    cout << "kd_g" << ": " << kd_g << endl;
    cout << "kd_b" << ": " << kd_b << endl;
    cout << "ks_r" << ": " << ks_r << endl;
    cout << "ks_g" << ": " << ks_g << endl;
    cout << "ks_b" << ": " << ks_b << endl;
    cout << "sp_v" << ": " << sp_v << endl;

    for(int i = 0; i < pl.size(); i++) {
      cout << "pl_x[" << i << "]" << ": " << pl[i].x << endl;
      cout << "pl_y[" << i << "]" << ": " << pl[i].y << endl;
      cout << "pl_z[" << i << "]" << ": " << pl[i].z << endl;
      cout << "pl_r[" << i << "]" << ": " << pl_r[i] << endl;
      cout << "pl_g[" << i << "]" << ": " << pl_g[i] << endl;
      cout << "pl_b[" << i << "]" << ": " << pl_b[i] << endl;
    }

    for(int i = 0; i < dl.size(); i++) {
      cout << "dl_x[" << i << "]" << ": " << dl[i].x << endl;
      cout << "dl_y[" << i << "]" << ": " << dl[i].y << endl;
      cout << "dl_z[" << i << "]" << ": " << dl[i].z << endl;
      cout << "dl_r[" << i << "]" << ": " << dl_r[i] << endl;
      cout << "dl_g[" << i << "]" << ": " << dl_g[i] << endl;
      cout << "dl_b[" << i << "]" << ": " << dl_b[i] << endl;
    }
  }
}

// Spacebar quit
void spacebarQuit(unsigned char key, int x, int y) {
  if(key == 32) {
    exit(0);
  }
}

// Allows us to define another main() function somewhere else.
// This allows us to run the tests
#ifndef _MAIN
#define _MAIN

int main(int argc, char *argv[]) {
  // parse args
  parseArgs(argc, argv);

  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  initScene();							// quick function to set up scene

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized

  glutKeyboardFunc(spacebarQuit);

  glutMainLoop();						// 999  //TODO: this is supposed to be infinityloop that will keep drawing and resizing
  // and whatever else

  return 0;
}


#endif




