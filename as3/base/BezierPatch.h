#ifndef BEZIER_PATCH_H_
#define BEZIER_PATCH_H_

#include <glm/glm.hpp>
#include <vector>

#include "BezierPatch.h"
#include "PointDeriv.h"
#include "PointNormal.h"

using namespace glm;
using namespace std;

class BezierPatch {
  public:
    // the 16 points that make up the surface
    vector<vec3> points; 
    float param;
    vector<PointNormal> surface_points;

    BezierPatch(vector<vec3> points) {
      this->points = points;
    }
    
    //given control points and param, find curve point and derivative
    PointDeriv bezcurveinterp(vec3 curve[], float u) {

      vec3 P0 = curve[0];
      vec3 P1 = curve[1];
      vec3 P2 = curve[2];
      vec3 P3 = curve[3];

      //split 3 segments into 2
      vec3 A = P0 * (1.0f-u) + P1 * u;
      vec3 B = P1 * (1.0f-u) + P2 * u;
      vec3 C = P2 * (1.0f-u) + P3 * u;

      //split 2 segments into 1
      vec3 D = A * (1.0-u) + B * u;
      vec3 E = B * (1.0-u) + C * u;
      
      //pick the point
      vec3 p = D * (1.0-u) + E * u;

      //compute and store derive
      vec3 dPdu = 3 * (E - D);

      return PointDeriv(p, dPdu);
    }

    //given control patch and (u,v) fine surface point and normal
    vec3 bezpatchinterp(float u, float v) {
      
      //Build control points for Patch in V
      PointDeriv vcurve[4];
      vec3 vcurve1[] = {points[0],points[1],points[2],points[3]};
      vec3 vcurve2[] = {points[4],points[5],points[6],points[7]};
      vec3 vcurve3[] = {points[8],points[9],points[10],points[11]};
      vec3 vcurve4[] = {points[12],points[13],points[14],point[15]};
      vcurve[0] = bezcurveinterp(vcurve1);
      vcurve[1] = bezcurveinterp(vcurve2);
      vcurve[2] = bezcurveinterp(vcurve3);
      vcurve[3] = bezcurveinterp(vcurve4);
 
      //Build control point for Patch in U
      PointDeriv ucurve[4];
      vec3 ucurve1 = {points[0],points[4],points[8],points[12]};
      vec3 ucurve2 = {points[1],points[5],points[9],points[13]};
      vec3 ucurve3 = {points[2],points[6],points[10],points[14]};
      vec3 ucurve4 = {points[3],points[7],points[11],points[15]};
      ucurve[0] = bezcurveinterp(ucurve1);
      ucurve[1] = bezcurveinterp(ucurve2);
      ucurve[2] = bezcurveinterp(ucurve3);
      ucurve[3] = bezcurveinterp(ucurve4);

      //evaluate surface and derivative for u and v
      PointDeriv vcurve_point = bezcurveinterp(vcurve, v);
      PointDeriv ucurve_point = bezcurveinterp(ucurve, u);

      //take cross product of partials to find normal
      vec3 n = cross(vcurve_point.derivative, ucurve_point.derivative);
      n = normalize(n);

      return PointNormal(vcurve_point.p, n);

    }

    void subdividepatch(void) {
      float epsilon = 0.001;
      int numdiv = ((1+epsilon)/param);

      //for each parametric value of u
      for (int iu = 0; iu < numdiv; iu++) {
        u = iu*param;

        //for each parametric value v
        for (int iv = 0; iv<numdiv; iv++) {
          v = iv*param;

          //evaluate surface
          PointNormal curr = bezpatchinterp(u, v);
          savesurfacepointnormal(curr);
        }
      }
    }

    void savesurfacepointnormal(PointNormal pn) {
      surface_points.push_back(pn);
    }

    void render(void) {
      //default: flat shading ("s" goes to smooth)
      //default: filled polygons ("w" goes to wireframe)
      int numdiv = 1.001/param;
      int horiz_squares = numdiv - 1;
      int vert_squares = numdiv - 1;
      for (int y = 0; y < vert_squares; y++) {
        for (int x = 0; x < horiz_squares; x++) {
          //normal before each vertex??
          //how to determine shading/color for square??
          glBegin(GL_Quad) {
            glnormal();
            glVertex(surface_points[x+y*numdiv]);
            glVertex(surface_points[x+1+y*numdiv]);
            glVertex(surface_points[x+1+(y+1)*numdiv]);
            glVertex(surface_points[x+(y+1)*numdiv]);
            glEnd();
          }
        }
      }
    }
};

#endif


