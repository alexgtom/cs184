#ifndef PIXEL_OPS_H_
#define PIXEL_OPS_H_

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


float sp_v = 0.0f;

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

    Color ka;
    Color kd;
    Color ks;
    float kr; // shineness

    // r, g, b, are values between [0.0f, 1.9f]
    Color c;

    PixelOps(Vector v) : v(v) {
      Color c;
      kr = 1;
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
      float m = pow(max(0.0f, reflected_direction.dot(viewer_direction)), kr);

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
// Draw a filled circle.  
//****************************************************


//void circle(float centerX, float centerY, float radius) {
//  // Draw inner circle
//  glBegin(GL_POINTS);
//
//  // We could eliminate wasted work by only looping over the pixels
//  // inside the sphere's radius.  But the example is more clear this
//  // way.  In general drawing an object by loopig over the whole
//  // screen is wasteful.
//
//  int i,j;  // Pixel indices
//
//  int minI = max(0,(int)floor(centerX-radius));
//  int maxI = min(viewport.w-1,(int)ceil(centerX+radius));
//
//  int minJ = max(0,(int)floor(centerY-radius));
//  int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));
//
//  for (i=0;i<viewport.w;i++) {
//    for (j=0;j<viewport.h;j++) {
//
//      // Location of the center of pixel relative to center of sphere
//      float x = (i+0.5-centerX);
//      float y = (j+0.5-centerY);
//
//      float dist = sqrt(sqr(x) + sqr(y));
//
//      if (dist<=radius) {
//
//        // This is the front-facing Z coordinate
//        float z = sqrt(radius*radius-dist*dist);
//
//        // normalize x, y, and z into coordinate system
//        PixelOps po(Vector(x / radius, y / radius, z / radius));
//
//        // iterate through each point light
//        for(int a = 0; a < pl_vector.size(); a++) {
//          po.renderPointLight(pl_vector[a], pl_color[a]);
//        }
//
//        // iterate through each directional light
//        for(int a = 0; a < dl_vector.size(); a++) {
//          po.renderDirectionalLight(dl_vector[a], dl_color[a]);
//        }
//
//        setPixel(i, j, po.c.r, po.c.g, po.c.b);
//
//        // This is amusing, but it assumes negative color values are treated reasonably.
//        // setPixel(i,j, x/radius, y/radius, z/radius );
//      }
//    }
//  }
//
//
//  glEnd();
//}

#endif
