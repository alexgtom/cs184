#ifndef BEZIER_PATCH_H_
#define BEZIER_PATCH_H_

#include <glm/glm.hpp>
#include <vector>
#include <iostream>


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
#include "PointDeriv.h"
#include "PointNormal.h"

#define EPSILON 0.001

using namespace glm;
using namespace std;

class BezierPatch {
  public:
    // the 16 points that make up the surface
    vector<vec3> points; 
    float step;
    vector<PointNormal> surface_points;
    
    BezierPatch() {}
    BezierPatch(vector<vec3> points, float subdivisionParameter) {
      this->points = points;
      this->step = subdivisionParameter;
      subdividepatch();
    }
    
    //given control points and step, find curve point and derivative
    virtual PointDeriv bezcurveinterp(vec3 curve[], float u) {

      vec3 P0 = curve[0];
      vec3 P1 = curve[1];
      vec3 P2 = curve[2];
      vec3 P3 = curve[3];

      //split 3 segments into 2
      vec3 A = P0 * (1.0f-u) + P1 * u;
      vec3 B = P1 * (1.0f-u) + P2 * u;
      vec3 C = P2 * (1.0f-u) + P3 * u;

      //split 2 segments into 1
      vec3 D = A * (1.0f-u) + B * u;
      vec3 E = B * (1.0f-u) + C * u;
      
      //pick the point
      vec3 p = D * (1.0f-u) + E * u;

      //compute and store derive
      vec3 dPdu = 3.0f * (E - D);

      return PointDeriv(p, dPdu);
    }

    //given control patch and (u,v) find surface point and normal
    virtual PointNormal bezpatchinterp(float u, float v) {
      
      //Build control points for Patch in V
      PointDeriv vcurve[4];
      vec3 vcurve1[] = {points[0],points[1],points[2],points[3]};
      vec3 vcurve2[] = {points[4],points[5],points[6],points[7]};
      vec3 vcurve3[] = {points[8],points[9],points[10],points[11]};
      vec3 vcurve4[] = {points[12],points[13],points[14],points[15]};
      vcurve[0] = bezcurveinterp(vcurve1, u);
      vcurve[1] = bezcurveinterp(vcurve2, u);
      vcurve[2] = bezcurveinterp(vcurve3, u);
      vcurve[3] = bezcurveinterp(vcurve4, u);
 
      //Build control point for Patch in U
      PointDeriv ucurve[4];
      vec3 ucurve1[] = {points[0],points[4],points[8],points[12]};
      vec3 ucurve2[] = {points[1],points[5],points[9],points[13]};
      vec3 ucurve3[] = {points[2],points[6],points[10],points[14]};
      vec3 ucurve4[] = {points[3],points[7],points[11],points[15]};
      ucurve[0] = bezcurveinterp(ucurve1, v);
      ucurve[1] = bezcurveinterp(ucurve2, v);
      ucurve[2] = bezcurveinterp(ucurve3, v);
      ucurve[3] = bezcurveinterp(ucurve4, v);

      //evaluate surface and derivative for u and v
      vec3 vcurve_points [] = {vcurve[0].point, vcurve[1].point, vcurve[2].point, vcurve[3].point};
      vec3 ucurve_points [] = {ucurve[0].point, ucurve[1].point, ucurve[2].point, ucurve[3].point};
      PointDeriv vcurve_point = bezcurveinterp(vcurve_points, v);
      PointDeriv ucurve_point = bezcurveinterp(ucurve_points, u);

      //take cross product of partials to find normal
      vec3 n = cross(ucurve_point.derivative, vcurve_point.derivative);
      
      // is this correct?
      if (dot(n, n) != 0.0)
        n = normalize(n);

      return PointNormal(ucurve_point.point, n);

    }

    virtual void subdividepatch(void) {
      int numdiv = ((1+EPSILON)/step);//+ 1;
      float u,v;

      //for each stepetric value of u
      for (int iu = 0; iu <= numdiv; iu++) {
        u = iu*step;

        //for each stepetric value v
        for (int iv = 0; iv<=numdiv; iv++) {
          v = iv*step;

          //evaluate surface
          PointNormal curr = bezpatchinterp(u, v);
          savesurfacepointnormal(curr);
        }
      }
    }

    virtual void savesurfacepointnormal(PointNormal pn) {
      surface_points.push_back(pn);
    }

    virtual void render_wireframe(void) {
      //default: flat shading ("s" goes to smooth)
      //default: filled polygons ("w" goes to wireframe)
      int numdiv = (1 + EPSILON)/step + 1;
      int horiz_squares = numdiv - 1;
      int vert_squares = numdiv - 1;
      for (int y = 0; y < vert_squares; y++) {
        for (int x = 0; x < horiz_squares; x++) {
	  // glBegin(GL_LINES);
          vec3 UL = surface_points[x+y*numdiv].point;
          vec3 UR = surface_points[x+1+y*numdiv].point;
          vec3 LR = surface_points[x+1+(y+1)*numdiv].point;
          vec3 LL = surface_points[x+(y+1)*numdiv].point;
          glBegin(GL_LINES);
	  glVertex3f(UL.x, UL.y, UL.z);
          glVertex3f(UR.x, UR.y, UR.z);
	  glEnd();
	  glBegin(GL_LINES);
	  glVertex3f(UR.x, UR.y, UR.z);
	  glVertex3f(LR.x, LR.y, LR.z);
	  glEnd();
	  glBegin(GL_LINES);
	  glVertex3f(LR.x, LR.y, LR.z);
	  glVertex3f(LL.x, LL.y, LL.z);
	  glBegin(GL_LINES);
	  glVertex3f(LL.x, LL.y, LL.z);
	  glVertex3f(UL.x, UL.y, UL.z);
	  glEnd();
	  //glBegin(GL_LINES);
	  //glVertex3f(LL.x, LL.y, LL.z);
	  //glVertex3f(UR.x, UR.y, UR.z);
	  //glEnd();
        }
      }
    }

    virtual void render_filled(void) {
      int numdiv = (1 + EPSILON)/step + 1;
      int horiz_squares = numdiv - 1;
	int vert_squares = numdiv - 1;
      for (int y = 0; y < vert_squares; y++) {
        for (int x = 0; x < horiz_squares; x++) {
          glBegin(GL_POLYGON);
          PointNormal UL = surface_points[x+y*numdiv];
          PointNormal UR = surface_points[x+1+y*numdiv];
          PointNormal LR = surface_points[x+1+(y+1)*numdiv];
          PointNormal LL = surface_points[x+(y+1)*numdiv];

          glNormal3f(UL.normal.x, UL.normal.y, UL.normal.z);
          glVertex3f(UL.point.x, UL.point.y, UL.point.z);
          glNormal3f(UL.normal.x, UL.normal.y, UL.normal.z);
          glVertex3f(UR.point.x, UR.point.y, UR.point.z);
          glNormal3f(LR.normal.x, LR.normal.y, LR.normal.z);
          glVertex3f(LR.point.x, LR.point.y, LR.point.z);
          glNormal3f(LL.normal.x, LL.normal.y, LL.normal.z);
          glVertex3f(LL.point.x, LL.point.y, LL.point.z);
          glEnd();
        }
      }
    }
};

#endif


