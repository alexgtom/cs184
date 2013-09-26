
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

#include "Vector.h"
#include "Color.h"


#define PI 3.14159265  // Should be used from mathlib
#define DEBUG_ARGS false
inline float sqr(float x) { return x*x; }

using namespace std;


//****************************************************
// Arguments
//****************************************************

Color ka;
Color kd;
Color ks;

float sp_v = 0.0f;

// there can be multuple light sources
vector<Vector> pl_vector;
vector<Color> pl_color;

vector<Vector> dl_vector;
vector<Color> dl_color;

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

class PixelOps;

class PixelOps {
  public:
    // coordinates on sphere
    Vector v;

    // r, g, b, are values between [0.0f, 1.9f]
    Color c;

    PixelOps(Vector v) : v(v) {
      Color c;
    }

    /* 
     * Ambient Component
     */
    PixelOps& ambientComponent(Color ambient_color) {
      // add ambient component
      this->c += ka * ambient_color;

      return *this;
    }

    /*
     * Diffuse Shading
     *
     * x, y, z is the direction of the light
     */
    PixelOps& diffuseComponent(Vector light_direction, Color light_color) {
      // light vector
      light_direction = light_direction.norm();

      // normal vector
      Vector normal = this->v.norm();
    
      // max(0, n.v)
      float m = max(0.0f, light_direction.dot(normal));
      
      // add diffuse component
      this->c += m * kd * light_color;
      
      return *this;
    }

    /*
     * Specular Component
     */
    PixelOps& specularComponent(Vector light_direction, Color light_color) {
      // light vector
      light_direction = light_direction.norm();

      // normal vector
      Vector normal = this->v.norm();

      // reflected direction
      Vector reflected_direction = -light_direction + (2 * light_direction.dot(normal) * normal);
      reflected_direction = reflected_direction.norm();

      // viewer direction
      Vector viewer_direction = Vector(0, 0, 1); //normalized

      // max term
      float m = max(0.0f, reflected_direction.dot(viewer_direction));

      // add specular component
      this->c += pow(m, sp_v) * ks * light_color;

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
      this->c = o * this->c;

      return *this;
    }

    /*
     * Calculate everything
     */
    void renderDirectionalLight(Vector light_direction, Color light_color) {
      ambientComponent(light_color);
      diffuseComponent(-light_direction, light_color);
      specularComponent(-light_direction, light_color);
    }

    void renderPointLight(Vector light_location, Color light_color) {
      ambientComponent(light_color);

      // make light shine to point
      diffuseComponent(light_location - this->v, light_color);
      specularComponent(light_location - this->v, light_color);
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
        PixelOps po(Vector(x / radius, y / radius, z / radius));

        // iterate through each point light
        for(int a = 0; a < pl_vector.size(); a++) {
          po.renderPointLight(pl_vector[a], pl_color[a]);
        }

        // iterate through each directional light
        for(int a = 0; a < dl_vector.size(); a++) {
          po.renderDirectionalLight(dl_vector[a], dl_color[a]);
        }

        setPixel(i, j, po.c.r, po.c.g, po.c.b);

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

  glClear(GL_COLOR_BUFFER_BIT);	  // clear the color buffer

  glMatrixMode(GL_MODELVIEW);			// indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"

  // Start drawing
  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glFlush();
  glutSwapBuffers();					    // swap buffers (we earlier set double buffer)
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
      ka = Color(atof(argv[i + 1]), 
                 atof(argv[i + 2]), 
                 atof(argv[i + 3]));
      i += 4;
    } else if (strcmp(option, "-kd") == 0) {
      kd = Color(atof(argv[i + 1]), 
                 atof(argv[i + 2]), 
                 atof(argv[i + 3]));
      i += 4;
    } else if (strcmp(option, "-ks") == 0) {
      ks = Color(atof(argv[i + 1]), 
                 atof(argv[i + 2]), 
                 atof(argv[i + 3]));
      i += 4;
    } else if (strcmp(option, "-sp") == 0) {
      sp_v = atof(argv[i + 1]);
      i += 2;
    } else if (strcmp(option, "-pl") == 0) {
      pl_vector.push_back(Vector(atof(argv[i + 1]), 
                                 atof(argv[i + 2]), 
                                 atof(argv[i + 3])));
      pl_color.push_back(Color(atof(argv[i + 4]), 
                               atof(argv[i + 5]), 
                               atof(argv[i + 6])));
      i += 7;
    } else if (strcmp(option, "-dl") == 0) {
      dl_vector.push_back(Vector(atof(argv[i + 1]), 
                                 atof(argv[i + 2]), 
                                 atof(argv[i + 3])));
      dl_color.push_back(Color(atof(argv[i + 4]), 
                               atof(argv[i + 5]), 
                               atof(argv[i + 6])));
      i += 7;
    } else {
      cerr << "Invalid argument: " << option << endl;
      exit(1);
    }
  }

  if (DEBUG_ARGS) {
    cout << "---[ ARGS PARSED ] -------------------" << endl;
    cout << "ka_r" << ": " << ka.r << endl;
    cout << "ka_g" << ": " << ka.g << endl;
    cout << "ka_b" << ": " << ka.b << endl;
    cout << "kd_r" << ": " << kd.r << endl;
    cout << "kd_g" << ": " << kd.g << endl;
    cout << "kd_b" << ": " << kd.b << endl;
    cout << "ks_r" << ": " << ks.r << endl;
    cout << "ks_g" << ": " << ks.g << endl;
    cout << "ks_b" << ": " << ks.b << endl;
    cout << "sp_v" << ": " << sp_v << endl;

    for(int i = 0; i < pl_vector.size(); i++) {
      cout << "pl_x[" << i << "]" << ": " << pl_vector[i].x << endl;
      cout << "pl_y[" << i << "]" << ": " << pl_vector[i].y << endl;
      cout << "pl_z[" << i << "]" << ": " << pl_vector[i].z << endl;
      cout << "pl_r[" << i << "]" << ": " << pl_color[i].r << endl;
      cout << "pl_g[" << i << "]" << ": " << pl_color[i].g << endl;
      cout << "pl_b[" << i << "]" << ": " << pl_color[i].b << endl;
    }

    for(int i = 0; i < dl_vector.size(); i++) {
      cout << "dl_x[" << i << "]" << ": " << dl_vector[i].x << endl;
      cout << "dl_y[" << i << "]" << ": " << dl_vector[i].y << endl;
      cout << "dl_z[" << i << "]" << ": " << dl_vector[i].z << endl;
      cout << "dl_r[" << i << "]" << ": " << dl_color[i].r << endl;
      cout << "dl_g[" << i << "]" << ": " << dl_color[i].g << endl;
      cout << "dl_b[" << i << "]" << ": " << dl_color[i].b << endl;
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




